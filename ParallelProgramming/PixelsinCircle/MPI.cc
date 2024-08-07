#include <assert.h>
#include <stdio.h>
#include <math.h>
#include <mpi.h>
using namespace std;

int main(int argc, char** argv) {
	if (argc != 3) {
		fprintf(stderr, "must provide exactly 2 arguments!\n");
		return 1;
	}

	unsigned long long r = atoll(argv[1]);
	unsigned long long k = atoll(argv[2]);
	unsigned long long pixels = 0;
	unsigned long long sum = 0;
  MPI_Status status;

	MPI_Init(&argc,&argv); 

	int rank, size;
	MPI_Comm_size(MPI_COMM_WORLD, &size); 
	MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
	//printf ("Number of tasks= %d My rank= %d\n", rank, size);

	unsigned long long n = r / size;
	unsigned long long start = n*rank;
	unsigned long long end = (rank == size-1) ?r :start+n;

	for(unsigned long long x = start; x < end; x++) {
		unsigned long long y = ceil(sqrtl(r*r - x*x));
		pixels += y;
		pixels %= k;
	}

	//MPI_Reduce(&pixels, &sum, 1, MPI_UNSIGNED_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);

	if(rank == 0){
		for(unsigned int x = 1; x < size; x++){
			MPI_Recv(&sum, 4, MPI_UNSIGNED_LONG_LONG, x, 1, MPI_COMM_WORLD, &status);
			pixels += sum;
			pixels %= k;
		}
		printf("%llu\n", (pixels * 4) % k);
	}else{
    	MPI_Send(&pixels, 4, MPI_UNSIGNED_LONG_LONG, 0, 1, MPI_COMM_WORLD);   
	}
	MPI_Finalize ();
  return 0;
}