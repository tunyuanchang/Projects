#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <random>
#include <algorithm>
#include <fstream>
#include <chrono>
using namespace std;
#define N 100000000
int n;
double points[N];
double true_slope, true_intercept;
double best_slope, best_intercept;
const int K =  1000*2; // num of iteration
const double T = 1e-4; // threshold
const int B = 32; // blolck size (max num of thread per block)

__global__ void calculateInliers(double *d_points,  bool*d_inliers, double threshold, double slope, double intercept, int n, int iter, size_t pitch){
    int point_idx = blockDim.x * blockIdx.x + threadIdx.x;
    if(point_idx >= n) return;
    double expected_y = slope * d_points[2*point_idx] + intercept;
    double error = fabs(d_points[2*point_idx+1] - expected_y);
    d_inliers[pitch * iter + point_idx] = (error < threshold);
}

__global__ void countInliers(int *d_inliers_cnt,  bool*d_inliers, int n ,int max_iter,size_t pitch){
    const int iter_idx = blockDim.x * blockIdx.x + threadIdx.x;
    if(iter_idx >= max_iter) return;
    int inliers_cnt = 0;
    for(int i=0;i<n;i++){
        if(d_inliers[pitch*iter_idx + i]){
            inliers_cnt++;
        }
    }
    d_inliers_cnt[iter_idx] = inliers_cnt; 
}

__global__ void findBestInliers(int *d_inliers_cnt, int* d_best_idx, int max_iter){
    int best_idx = -1;
    int best_inliers_cnt = 0;
    int cnt = 0;
    for(int i = 0; i< max_iter; i++){
        cnt = d_inliers_cnt[i];
        if (cnt > best_inliers_cnt) {
            best_inliers_cnt = cnt;
            best_idx = i;
        }
    }
    d_best_idx[0] = best_idx;
}

// Function to perform 2D linear regression using RANSAC
void linearRegressionRANSAC(int iterations, double threshold) {
    mt19937 gen(0);
    uniform_int_distribution<int> dist(0, n - 1);

    int inliers[n];
    int best_inliers_cnt = 0;
    int best_inlier[n];
    double *d_points;
    bool *d_inliers;


    // allocate GPU memory for points arrya & inlier matrix 
    cudaMalloc((void**)&d_points, 2 * n * sizeof(double));
    cudaMemcpy(d_points, points, 2 * n * sizeof(double), cudaMemcpyHostToDevice);

    size_t pitch = n;
	//cudaMallocPitch((void**)&d_inliers, &pitch, n * K * sizeof(bool), n);
    cudaMalloc((void**)&d_inliers, n * K * sizeof(bool));

    int block_size = B;
    dim3 block_dim(block_size, 1);
    int grid_size = int( ceil(float(n)/float(B)) );
    dim3 grid_dim(grid_size, 1);
    cout << "block size: " << block_size << endl;
    cout << "grid size: " << grid_size  << endl;
    double x1, y1, x2, y2;
    int idx1, idx2;
    double slope, intercept;

    for (int i = 0; i < iterations; i++) {
        // Randomly select two points
        idx1 = dist(gen);
        idx2 = dist(gen);

        x1 = points[2*idx1];
        y1 = points[2*idx1 + 1];
        x2 = points[2*idx2];
        y2 = points[2*idx2 + 1];

        // Calculate slope and intercept
        slope = (y2 - y1) / (x2 - x1 + 1e-4);
        intercept = y1 - slope * x1;

        // check to see if each point is inlier //GPU O(n) -> O(1)
        calculateInliers<<<grid_dim, block_dim>>>(d_points, d_inliers, threshold, slope, intercept, n, i , pitch);
        cudaError_t err = cudaGetLastError();
        if(err!=cudaSuccess){
            cout << "cuda error:" << cudaGetErrorString(err) << endl;
        }        
    }

    int* d_inliers_cnt;
    int* d_best_idx;
    // malloc memory on GPU for inliers count of each round (K rounds)
    cudaMalloc((void**)&d_inliers_cnt, K * sizeof(int));
    // malloc memory on GPU for max inliers index
    cudaMalloc((void**)&d_best_idx, sizeof(int));
  
    auto start = chrono::steady_clock::now();
    // calculate inliers cnt for each round  //GPU
    block_size = B;
    grid_size = int( ceil(float(K)/float(B)) );
    dim3 grid_dim_2(grid_size, 1);
    dim3 block_dim_2(block_size, 1);
    countInliers<<<grid_dim_2, block_dim_2>>>(d_inliers_cnt,  d_inliers, n , K, pitch);

    // find best inliers //GPU
    block_size = 1;
    grid_size = 1;
    dim3 grid_dim_3(grid_size, 1);
    dim3 block_dim_3(block_size, 1);
    findBestInliers<<<grid_dim_3, block_dim_3>>>(d_inliers_cnt, d_best_idx, K);

    // copy best inliers indices back to host
    int* best_idx = (int*)malloc(sizeof(int));
    cudaMemcpy(best_idx, d_best_idx, sizeof(int), cudaMemcpyDeviceToHost);
    bool* is_inlier = (bool*)malloc(n * sizeof(bool));
    cudaMemcpy(is_inlier, d_inliers + pitch*(*best_idx), n * sizeof(bool), cudaMemcpyDeviceToHost);

    // CPU
    best_inliers_cnt = 0;
    for(int i=0;i<n;i++){
        if(is_inlier[i]){
            best_inlier[best_inliers_cnt++] = i;
        }
    }

    auto end = chrono::steady_clock::now();
    cout << "best inliers count: " << best_inliers_cnt << endl;
    cout << "best index: " << *best_idx << endl;
    cout << "===================================" << endl;
    cout << "Time for finding best inliers: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " millisecond." << endl;
    cout << "===================================" << endl;
    
    cudaFree(d_points);
    cudaFree(d_inliers);
    cudaFree(d_inliers_cnt);
    cudaFree(d_best_idx);


    // Regression using best inliers
    double sum_x = 0, sum_y = 0, sum_xy = 0, sum_xx = 0;

    for (int i = 0; i < best_inliers_cnt; i++) {
        double x_val = points[2*best_inlier[i]];
        double y_val = points[2*best_inlier[i] + 1];
        sum_x += x_val;
        sum_y += y_val;
        sum_xy += x_val * y_val;
        sum_xx += x_val * x_val;
    }
    
    double mean_x = sum_x / best_inliers_cnt;
    double mean_y = sum_y / best_inliers_cnt;

    best_slope = (sum_xy - best_inliers_cnt * mean_x * mean_y) / (sum_xx - best_inliers_cnt * mean_x * mean_x);
    best_intercept = mean_y - best_slope * mean_x;
    
    return;
}

int main(int argc, char *argv[]) {
    //input
    ifstream infile(argv[1]);

    infile >> true_slope >> true_intercept;

    int i = 0;
    double x, y;
    while (infile >> x >> y){
        points[i++] = x;
        points[i++] = y;
    }
    n = (i + 1) / 2;
    cout << "Count: " << n << endl;
    auto start = chrono::steady_clock::now();
    linearRegressionRANSAC(K, T);
    auto end = chrono::steady_clock::now();

    // Display the result
    cout << "===================================" << endl;
    cout << "Estimated Slope: " << best_slope << endl;
    cout << "Estimated Intercept: " << best_intercept << endl;
    cout << "===================================" << endl;
    cout << "Ground Truth Slope: " << true_slope << endl;
    cout << "Ground Truth Intercept: " << true_intercept << endl;
    cout << "===================================" << endl;
    cout << "Time for RANSAC: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " millisecond." << endl;
    cout << "Time for RANSAC: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " microsecond." << endl;
    return 0;
}