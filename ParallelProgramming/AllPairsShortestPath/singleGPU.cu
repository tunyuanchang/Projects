#include <stdio.h>
#include <stdlib.h>
#include <cassert>
#include <iostream>
#include <cuda.h>

using namespace std;

#define BLOCK_SIZE 64
#define HALF_BLOCK_SIZE BLOCK_SIZE/2

__global__ void Phase1(int *dist, int Round, int n);
__global__ void Phase2(int *dist, int Round, int n);
__global__ void Phase3(int *dist, int Round, int n);

int n, m, _n;
const int INF = 1073741823;
int *Dist = NULL;

int ceil(int a, int b){ return (a + b - 1) / b;}

void block_FW(){
    int *dist = NULL;

    const unsigned long matrixSize = n * n * sizeof(int);
    cudaHostRegister(Dist, matrixSize, cudaHostRegisterDefault);
    cudaMalloc(&dist, matrixSize);
    cudaMemcpy(dist, Dist, matrixSize, cudaMemcpyHostToDevice);

    const int num_blocks = ceil(n, BLOCK_SIZE);
    dim3 block_dim(HALF_BLOCK_SIZE, HALF_BLOCK_SIZE, 1);
    dim3 grid_dim(num_blocks, num_blocks, 1);

    const int round = ceil(n, BLOCK_SIZE);
    
    for (int r = 0; r < round; ++r){
        Phase1<<<1, block_dim>>>(dist, r, n);
        Phase2<<<num_blocks, block_dim>>>(dist, r, n);
        Phase3<<<grid_dim, block_dim>>>(dist, r, n);
    }

    cudaMemcpy(Dist, dist, matrixSize, cudaMemcpyDeviceToHost);
    cudaFree(dist);
    
    return;
}

__global__ void Phase1(int *dist, int Round, int n){
    __shared__ int shared_memory[BLOCK_SIZE][BLOCK_SIZE];
    int i = threadIdx.y;
    int j = threadIdx.x;
    int half_i = i + HALF_BLOCK_SIZE;
    int half_j = j + HALF_BLOCK_SIZE;
    int offset = BLOCK_SIZE * Round;

    shared_memory[i][j] = dist[offset * (n + 1) + i * n + j];
    shared_memory[half_i][j] = dist[offset * (n + 1) + half_i * n + j];
    shared_memory[i][half_j] = dist[offset * (n + 1) + i * n + half_j];
    shared_memory[half_i][half_j] = dist[offset * (n + 1) + half_i * n + half_j];
    __syncthreads();

    for (int k = 0; k < BLOCK_SIZE; k++){
        shared_memory[i][j] = min(shared_memory[i][j], shared_memory[i][k] + shared_memory[k][j]);
        shared_memory[half_i][j] = min(shared_memory[half_i][j], shared_memory[half_i][k] + shared_memory[k][j]);
        shared_memory[i][half_j] = min(shared_memory[i][half_j], shared_memory[i][k] + shared_memory[k][half_j]);
        shared_memory[half_i][half_j] = min(shared_memory[half_i][half_j], shared_memory[half_i][k] + shared_memory[k][half_j]);
        __syncthreads();
    }

    dist[offset * (n + 1) + i * n + j] = shared_memory[i][j];
    dist[offset * (n + 1) + half_i * n + j] = shared_memory[half_i][j];
    dist[offset * (n + 1) + i * n + half_j] = shared_memory[i][half_j];
    dist[offset * (n + 1) + half_i * n + half_j] = shared_memory[half_i][half_j];
    
    return;
}

__global__ void Phase2(int *dist, int Round, int n){
    __shared__ int pivot[BLOCK_SIZE][BLOCK_SIZE];
    __shared__ int row_blocks[BLOCK_SIZE][BLOCK_SIZE];
    __shared__ int col_blocks[BLOCK_SIZE][BLOCK_SIZE];

    int i = threadIdx.y;
    int j = threadIdx.x;
    int block_i = blockIdx.x;
    int half_i = i + HALF_BLOCK_SIZE;
    int half_j = j + HALF_BLOCK_SIZE;
    int offset = BLOCK_SIZE * Round;

    if (block_i == Round) return;

    row_blocks[i][j] = dist[(block_i * BLOCK_SIZE + i) * n + offset + j];
    row_blocks[half_i][j] = dist[(block_i * BLOCK_SIZE + half_i) * n + offset + j];
    row_blocks[i][half_j] = dist[(block_i * BLOCK_SIZE + i) * n + offset + half_j];
    row_blocks[half_i][half_j] = dist[(block_i * BLOCK_SIZE + half_i) * n + offset + half_j];

    col_blocks[i][j] = dist[(offset + i) * n + (block_i * BLOCK_SIZE + j)];
    col_blocks[half_i][j] = dist[(offset + half_i) * n + (block_i * BLOCK_SIZE + j)];
    col_blocks[i][half_j] = dist[(offset + i) * n + (block_i * BLOCK_SIZE + half_j)];
    col_blocks[half_i][half_j] = dist[(offset + half_i) * n + (block_i * BLOCK_SIZE + half_j)];

    pivot[i][j] = dist[offset * (n + 1) + i * n + j];
    pivot[half_i][j] = dist[offset * (n + 1) + half_i * n + j];
    pivot[i][half_j] = dist[offset * (n + 1) + i * n + half_j];
    pivot[half_i][half_j] = dist[offset * (n + 1) + half_i * n + half_j];
    __syncthreads();

    for (int k = 0; k < BLOCK_SIZE; k++){
        row_blocks[i][j] = min(row_blocks[i][j], row_blocks[i][k] + pivot[k][j]);
        row_blocks[half_i][j] = min(row_blocks[half_i][j], row_blocks[half_i][k] + pivot[k][j]);
        row_blocks[i][half_j] = min(row_blocks[i][half_j], row_blocks[i][k] + pivot[k][half_j]);
        row_blocks[half_i][half_j] = min(row_blocks[half_i][half_j], row_blocks[half_i][k] + pivot[k][half_j]);

        col_blocks[i][j] = min(col_blocks[i][j], pivot[i][k] + col_blocks[k][j]);
        col_blocks[half_i][j] = min(col_blocks[half_i][j], pivot[half_i][k] + col_blocks[k][j]);
        col_blocks[i][half_j] = min(col_blocks[i][half_j], pivot[i][k] + col_blocks[k][half_j]);
        col_blocks[half_i][half_j] = min(col_blocks[half_i][half_j], pivot[half_i][k] + col_blocks[k][half_j]);
    }

    dist[(block_i * BLOCK_SIZE + i) * n + offset + j] = row_blocks[i][j];
    dist[(block_i * BLOCK_SIZE + half_i) * n + offset + j] = row_blocks[half_i][j];
    dist[(block_i * BLOCK_SIZE + i) * n + offset + half_j] = row_blocks[i][half_j];
    dist[(block_i * BLOCK_SIZE + half_i) * n + offset + half_j] = row_blocks[half_i][half_j];

    dist[(offset + i)* n + (block_i * BLOCK_SIZE + j)] = col_blocks[i][j];
    dist[(offset + half_i) * n + (block_i * BLOCK_SIZE + j)] = col_blocks[half_i][j];
    dist[(offset + i) * n + (block_i * BLOCK_SIZE + half_j)] = col_blocks[i][half_j];
    dist[(offset + half_i) * n + (block_i * BLOCK_SIZE + half_j)] = col_blocks[half_i][half_j];
    
    return;
}

__global__ void Phase3(int *dist, int Round, int n){
    __shared__ int row_blocks[BLOCK_SIZE][BLOCK_SIZE];
    __shared__ int col_blocks[BLOCK_SIZE][BLOCK_SIZE];
    __shared__ int shared_memory[BLOCK_SIZE][BLOCK_SIZE];

    int i = threadIdx.y;
    int j = threadIdx.x;
    int block_i = blockIdx.y;
    int block_j = blockIdx.x;
    int half_i = i + HALF_BLOCK_SIZE;
    int half_j = j + HALF_BLOCK_SIZE;
    int offset = BLOCK_SIZE * Round;

    if (block_i == Round && block_j == Round) return;

    shared_memory[i][j] = dist[(block_i * BLOCK_SIZE + i) * n + (block_j * BLOCK_SIZE + j)];
    shared_memory[half_i][j] = dist[(block_i * BLOCK_SIZE + half_i) * n + (block_j * BLOCK_SIZE + j)];
    shared_memory[i][half_j] = dist[(block_i * BLOCK_SIZE + i) * n + (block_j * BLOCK_SIZE + half_j)];
    shared_memory[half_i][half_j] = dist[(block_i * BLOCK_SIZE + half_i) * n + (block_j * BLOCK_SIZE + half_j)];

    row_blocks[i][j] = dist[(block_i * BLOCK_SIZE + i) * n + offset + j];
    row_blocks[half_i][j] = dist[(block_i * BLOCK_SIZE + half_i) * n + offset + j];
    row_blocks[i][half_j] = dist[(block_i * BLOCK_SIZE + i) * n + offset + half_j];
    row_blocks[half_i][half_j] = dist[(block_i * BLOCK_SIZE + half_i) * n + offset + half_j];

    col_blocks[i][j] = dist[(offset + i) * n + (block_j * BLOCK_SIZE + j)];
    col_blocks[half_i][j] = dist[(offset + half_i) * n + (block_j * BLOCK_SIZE + j)];
    col_blocks[i][half_j] = dist[(offset + i) * n + (block_j * BLOCK_SIZE + half_j)];
    col_blocks[half_i][half_j] = dist[(offset + half_i) * n + (block_j * BLOCK_SIZE + half_j)];
    __syncthreads();

    for (int k = 0; k < BLOCK_SIZE; k++){
        shared_memory[i][j] = min(shared_memory[i][j], row_blocks[i][k] + col_blocks[k][j]);
        shared_memory[half_i][j] = min(shared_memory[half_i][j], row_blocks[half_i][k] + col_blocks[k][j]);
        shared_memory[i][half_j] = min(shared_memory[i][half_j], row_blocks[i][k] + col_blocks[k][half_j]);
        shared_memory[half_i][half_j] = min(shared_memory[half_i][half_j], row_blocks[half_i][k] + col_blocks[k][half_j]);
    }

    dist[(block_i * BLOCK_SIZE + i) * n + (block_j * BLOCK_SIZE + j)] = shared_memory[i][j];
    dist[(block_i * BLOCK_SIZE + half_i) * n + (block_j * BLOCK_SIZE + j)] = shared_memory[half_i][j];
    dist[(block_i * BLOCK_SIZE + i) * n + (block_j * BLOCK_SIZE + half_j)] = shared_memory[i][half_j];
    dist[(block_i * BLOCK_SIZE + half_i) * n + (block_j * BLOCK_SIZE + half_j)] = shared_memory[half_i][half_j];
    
    return;
}

int main(int argc, char *argv[]){
    // input
    FILE *infile = fopen(argv[1], "rb");
    if(infile == NULL) cout << "Fail to open file" << endl; 
    
    fread(&_n, sizeof(int), 1, infile);
    fread(&m, sizeof(int), 1, infile);
    
    n = BLOCK_SIZE * ceil(_n, BLOCK_SIZE); // padding, let n % BLOCK_SIZE == 0
    Dist = (int *)malloc(n * n * sizeof(int));
    
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            if (i == j) Dist[i * n + j] = 0;
            else Dist[i * n + j] = INF;
        }
    }

    int pair[3];
    while(m--){
        fread(pair, sizeof(int), 3, infile);
        Dist[pair[0] * n + pair[1]] = pair[2];
    }
    fclose(infile);
    
    // calculate
    block_FW();

    // output
    FILE *outfile = fopen(argv[2], "w");
    for (int i = 0; i < _n; ++i){
        fwrite(&Dist[i * n], sizeof(int), _n, outfile);
    }
    fclose(outfile);

    cudaFreeHost(Dist);
    return 0;
}