#include <assert.h>
#include <stdio.h>
#include <math.h>
#include <pthread.h>

#define ULL unsigned long long
using namespace std;

ULL sum = 0, r, k, n;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* partial_sum(void* tid){
	ULL pixels = 0;
	int id = *(int*)tid;
	ULL start = n*(ULL)id;
	ULL end = (start + n >= r) ?r :start+n;

	for (ULL x = start; x < end; x++) {
		ULL y = ceil(sqrtl(r*r - x*x));
		pixels += y;
		if(x%10 == 0) pixels %= k;
	}

	pthread_mutex_lock(&mutex);
	sum += pixels;
	sum %= k;
	pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}
int main(int argc, char** argv) {
	if (argc != 3) {
		fprintf(stderr, "must provide exactly 2 arguments!\n");
		return 1;
	}
	r = atoll(argv[1]);
	k = atoll(argv[2]);
 
	cpu_set_t cpuset;
	sched_getaffinity(0, sizeof(cpuset), &cpuset);
	int ncpus = CPU_COUNT(&cpuset);

  n = ceil(r / (double)ncpus);
  ncpus = ceil(r / (long double)n);
	pthread_t threads[ncpus];
  int ID[ncpus];

	int rc;
	for(int t = 0; t < ncpus; t++){
    	ID[t] = t;
		  rc = pthread_create(&threads[t], NULL, partial_sum, (void*)&ID[t]);
		  if (rc){
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
      }
	}
	
	for(int t = 0; t < ncpus; t++){
		pthread_join(threads[t] , NULL);
	}
	printf("%llu\n", (4 * sum)%k);
	pthread_exit(NULL);
	return 0;
}
