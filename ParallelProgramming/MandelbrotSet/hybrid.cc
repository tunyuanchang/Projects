//pthread version
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#define PNG_NO_SETJMP
#include <sched.h>
#include <assert.h>
#include <png.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <mpi.h>
#include <omp.h>

int iters, width, height;
double left, right, lower, upper, chunk_y, chunk_x;
int* image = NULL;

void write_png(const char* filename, int iters, int width, int height, const int* buffer) {
    FILE* fp = fopen(filename, "wb");
    assert(fp);
    png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    assert(png_ptr);
    png_infop info_ptr = png_create_info_struct(png_ptr);
    assert(info_ptr);
    png_init_io(png_ptr, fp);
    png_set_IHDR(png_ptr, info_ptr, width, height, 8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
    png_set_filter(png_ptr, 0, PNG_NO_FILTERS);
    png_write_info(png_ptr, info_ptr);
    png_set_compression_level(png_ptr, 1);
    size_t row_size = 3 * width * sizeof(png_byte);
    png_bytep row = (png_bytep)malloc(row_size);
    for (int y = 0; y < height; ++y) {
        memset(row, 0, row_size);
        for (int x = 0; x < width; ++x) {
            int p = buffer[(height - 1 - y) * width + x];
            png_bytep color = row + x * 3;
            if (p != iters) {
                if (p & 16) {
                    color[0] = 240;
                    color[1] = color[2] = p % 16 * 16;
                } else {
                    color[0] = p % 16 * 16;
                }
            }
        }
        png_write_row(png_ptr, row);
    }
    free(row);
    png_write_end(png_ptr, NULL);
    png_destroy_write_struct(&png_ptr, &info_ptr);
    fclose(fp);
}

int main(int argc, char** argv) {
    /* detect how many CPUs are available */
    cpu_set_t cpu_set;
    sched_getaffinity(0, sizeof(cpu_set), &cpu_set);
    int ncpus = CPU_COUNT(&cpu_set);
    //printf("%d cpus available\n", CPU_COUNT(&cpu_set));

    /* initialization for mpi */
    MPI_Status status;
	MPI_Init(&argc,&argv); 
	int rank, size;
	MPI_Comm_size(MPI_COMM_WORLD, &size); 
	MPI_Comm_rank(MPI_COMM_WORLD, &rank); 

    /* argument parsing */
    assert(argc == 9);
    iters = strtol(argv[2], 0, 10);
    left = strtod(argv[3], 0);
    right = strtod(argv[4], 0);
    lower = strtod(argv[5], 0);
    upper = strtod(argv[6], 0);
    width = strtol(argv[7], 0, 10);
    height = strtol(argv[8], 0, 10);

    long yCount = ceil(height / (double)size);
    long y_start = yCount*rank;
    long y_end = (y_start + yCount >= height) ?height :y_start+yCount;

    /* allocate memory for image */
    image = (int*)malloc(width * yCount * sizeof(int));
    assert(image);

    chunk_x = (right - left) / width;
    chunk_y = (upper - lower) / height;

    /* mandelbrot set */
    for (int j = y_start; j < y_end; ++j) {
        double y0 = j * chunk_y + lower;
        #pragma omp parallel for schedule(dynamic)
        for (int i = 0; i < width; ++i) {
            double x0 = i * chunk_x + left;

            int repeats = 0;
            double x = 0;
            double y = 0;
            double length_squared = 0;
            while (repeats < iters && length_squared < 4) {
                double temp = x * x - y * y + x0;
                y = 2 * x * y + y0;
                x = temp;
                length_squared = x * x + y * y;
                ++repeats;
            }
            image[(j - y_start) * width + i] = repeats;
        }
    }

    int* allImage = NULL;
    if(rank == 0){
        allImage = (int *)malloc(yCount * size * width * sizeof(int));
    }
    MPI_Gather(image, width * yCount, MPI_INT, allImage, width * yCount, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Finalize ();
    
    /* draw and cleanup */
    if(rank == 0){
        write_png(argv[1], iters, width, height, allImage);
    }
    free(image);
}
