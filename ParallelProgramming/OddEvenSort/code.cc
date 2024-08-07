#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <boost/sort/spreadsort/float_sort.hpp>
#include <mpi.h>

#define ODD_SORT 1
#define EVEN_SORT 2

unsigned int n, num, r, start;
float *tmp;

void MergeLow(float *data, float *Left, int dataCount, int LeftCount){
    if(Left[LeftCount-1] <= data[0]) return;
    int i = dataCount - 1, j = LeftCount - 1, k = dataCount - 1;
    while(k >= 0){
        if(i >= 0 && j >= 0){
            tmp[k--] = (data[i] >= Left[j]) ?data[i--] : Left[j--];
        }else if(i >= 0){
            tmp[k--] = data[i--];
        }else{
            tmp[k--] = Left[j--];
        }
    }
    for(k = 0; k < dataCount; k++)
        data[k] = tmp[k];
    return;
}

void MergeHigh(float *data, float *Right, int dataCount, int RightCount){
    if(data[dataCount-1] <= Right[0]) return;
    int i = 0, j = 0, k = 0;
    while(k < dataCount){
        if(i < dataCount && j < RightCount){
            tmp[k++] = (data[i] <= Right[j]) ?data[i++] : Right[j++];
        }else if(i < dataCount){
            tmp[k++] = data[i++];
        }else{
            tmp[k++] = Right[j++];
        }
    }
    for(k = 0; k < dataCount; k++)
        data[k] = tmp[k];
    return;
}

int main(int argc, char **argv){
    if(argc != 4){
  		fprintf(stderr, "Must provide 3 parameters\n");
  		return -1;
  	}

    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    n = atoi(argv[1]);

    MPI_File input_file, output_file;

    int count = 0;
    num = n / size, r = n % size;
    if(rank < r) count = num+1, start = count * rank;
	else count = num, start = count * rank + r;
    
    float *data, *buffer;
    if(count != 0){
        data = new float[count];
        buffer = new float[num+1];
        tmp = new float[count];
    }
    
    MPI_File_open(MPI_COMM_WORLD, argv[2], MPI_MODE_RDONLY, MPI_INFO_NULL, &input_file);
    if(count != 0) MPI_File_read_at(input_file, sizeof(float) * start, data, count, MPI_FLOAT, MPI_STATUS_IGNORE);
    MPI_File_close(&input_file);

    if(count != 0){
        // Local Sort
        boost::sort::spreadsort::float_sort(data, data + count);

        // Odd-Even Sort
        // Neighborhood
        int leftCount = (rank == 0) ?0 :(rank-1 < r ?num+1 :num);
        int rightCount = (rank == size-1) ?0 :(rank+1 < r ?num+1 :num);
    
        int loopCount = 0, r = rank & 1;
        while (loopCount <= size){
            if (r == 0){
                // check right
                if (rightCount != 0){
                    MPI_Sendrecv(&data[count-1], 1, MPI_FLOAT, rank + 1, EVEN_SORT, buffer, 1, MPI_FLOAT, rank + 1, EVEN_SORT, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                    if (data[count - 1] > buffer[0]){
                        MPI_Sendrecv(data, count, MPI_FLOAT, rank + 1, EVEN_SORT, buffer, rightCount, MPI_FLOAT, rank + 1, EVEN_SORT, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                        MergeHigh(data, buffer, count, rightCount);
                    }
                }
                // check left
                if (leftCount != 0){
                    MPI_Sendrecv(&data[0], 1, MPI_FLOAT, rank - 1, ODD_SORT, buffer, 1, MPI_FLOAT, rank - 1, ODD_SORT, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                    if (buffer[0] > data[0]){
                        MPI_Sendrecv(data, count, MPI_FLOAT, rank - 1, ODD_SORT, buffer, leftCount, MPI_FLOAT, rank - 1, ODD_SORT, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                        MergeLow(data, buffer, count, leftCount);
                    }
                }
            }else{
                // check left
                if(leftCount != 0){
                    MPI_Sendrecv(&data[0], 1, MPI_FLOAT, rank - 1, EVEN_SORT, buffer, 1, MPI_FLOAT, rank - 1, EVEN_SORT, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                    if (buffer[0] > data[0]){
                        MPI_Sendrecv(data, count, MPI_FLOAT, rank - 1, EVEN_SORT, buffer, leftCount, MPI_FLOAT, rank - 1, EVEN_SORT, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                        MergeLow(data, buffer, count, leftCount);
                    }
                }
                // check right
                if(rightCount != 0){
                    MPI_Sendrecv(&data[count - 1], 1, MPI_FLOAT, rank + 1, ODD_SORT, buffer, 1, MPI_FLOAT, rank + 1, ODD_SORT, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                    if (data[count - 1] > buffer[0]){
                        MPI_Sendrecv(data, count, MPI_FLOAT, rank + 1, ODD_SORT, buffer, rightCount, MPI_FLOAT, rank + 1, ODD_SORT, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                        MergeHigh(data, buffer, count, rightCount);
                    }
                }
            }
            loopCount += 2;
        }
    }
    
    MPI_File_open(MPI_COMM_WORLD, argv[3], MPI_MODE_CREATE|MPI_MODE_WRONLY, MPI_INFO_NULL, &output_file);
    MPI_File_write_at(output_file, sizeof(float) * start, data, count, MPI_FLOAT, MPI_STATUS_IGNORE);
    MPI_File_close(&output_file);
    MPI_Finalize();

    if(count != 0){
        delete[] data;
        delete[] buffer;
        delete[] tmp;
    }

    return 0;
}