#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <random>
#include <algorithm>
#include <fstream>
#include <chrono>

#include <openacc.h>

#define N 2000001
using namespace std;

int n;
double points[N];
double true_slope, true_intercept;
double best_slope, best_intercept;

// Function to perform 2D linear regression using RANSAC
void linearRegressionRANSAC(double *p, int iterations, double threshold) {
    mt19937 gen(0);
    uniform_int_distribution<int> dist(0, n - 1);

    int best_inliers_cnt = 0;
    int best_inlier[n];
    int inlier[n+1];
    
    #pragma acc data copyin(p[0:2*n]) create(best_inlier[0:n], inlier[0:n+1])
    {
        #pragma acc data present(p, best_inlier, inlier)
        for (int i = 0; i < iterations; i++) {
            // Randomly select two points
            int idx1 = 2*dist(gen);
            int idx2 = 2*dist(gen);

            double x1 = p[idx1];
            double y1 = p[idx1 + 1];
            double x2 = p[idx2];
            double y2 = p[idx2 + 1];

            // Calculate slope and intercept
            double slope = (y2 - y1) / (x2 - x1 + threshold);
            double intercept = y1 - slope * x1;

            // Count inliers
            int inliers_cnt = 0;
            
            #pragma acc parallel loop reduction(+: inliers_cnt)
            for (int i = 0; i < 2 * n; i += 2) {
                double expected_y = slope * p[i] + intercept;
                double error = fabs(p[i+1] - expected_y);
                
                if (error < threshold) {
                    inlier[inliers_cnt++] = i;
                }
            }

            // Update best model if we found more inliers
            if (inliers_cnt > best_inliers_cnt) {
                best_inliers_cnt = inliers_cnt;
                
                for(int i = 0; i < best_inliers_cnt; i++){
                    best_inlier[i] = inlier[i];
                }
            }
            
        }
        
        // Regression using best inliers
        double sum_x = 0.0;
        double sum_y = 0.0;
        double sum_xy = 0.0;
        double sum_xx = 0.0;
        
        #pragma acc parallel loop reduction(+: sum_x, sum_y, sum_xy, sum_xx)
        for (int i = 0; i < best_inliers_cnt; i++) {
            double x_val = p[best_inlier[i]];
            double y_val = p[best_inlier[i] + 1];
            sum_x += x_val;
            sum_y += y_val;
            sum_xy += x_val * y_val;
            sum_xx += x_val * x_val;
        }
        
        double mean_x = sum_x / best_inliers_cnt;
        double mean_y = sum_y / best_inliers_cnt;

        
        best_slope = (sum_xy - best_inliers_cnt * mean_x * mean_y) / (sum_xx - best_inliers_cnt * mean_x * mean_x);
        best_intercept = mean_y - best_slope * mean_x;
    }
    
    return;
}

bool InitCUDA(void) {
    int count = 0;

    count =  acc_get_num_devices(acc_device_nvidia);
    if(count == 0) {
        std::cerr << "There is no device.\n";
        return false;
    }

    acc_set_device_num(0, acc_device_nvidia);

    std::cout << "CUDA initialized.\n";
    return true;
}
int main(int argc, char *argv[]) {
    InitCUDA();
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
    
    double *p = new double[2 * n];
    
    for(int i = 0; i < 2 * n; i++){
      p[i] = points[i];
    }
    
    // Perform linear regression using RANSAC
    int iterations = 1000*2;
    double threshold = 1e-4;
    auto start = chrono::steady_clock::now();
    linearRegressionRANSAC(p, iterations, threshold);
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