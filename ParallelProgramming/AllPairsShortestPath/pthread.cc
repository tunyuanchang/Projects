#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
using namespace std;

const int INF = 1073741823;
const int V = 6001;

int n, m, ncpus, count;
static int Dist[V][V];
pthread_barrier_t barr;

void* calculate(void* arg){
    int id = *(int*)arg;

    int i_start = id * count;
    int i_end = i_start + count;
    if(i_end > n) i_end = n;

    for (int k = 0; k < n; k++) {
        for (int i = i_start; i < i_end; i++) {
            if (i == k || Dist[i][k] == INF) continue;
            for (int j = 0; j < n; j++) {
                if (k == j || Dist[k][j] == INF) continue;
                if (Dist[i][k] + Dist[k][j] < Dist[i][j]) {
                    Dist[i][j] = Dist[i][k] + Dist[k][j];
                }
            }
        }
        pthread_barrier_wait(&barr);
    }
    return NULL;
}

int main(int argc, char* argv[]) {
    FILE* infile = fopen(argv[1], "rb");
    fread(&n, sizeof(int), 1, infile);
    fread(&m, sizeof(int), 1, infile);

    for (int i = 0; i < n; ++i) {
        fill(Dist[i], Dist[i] + n, INF);
        Dist[i][i] = 0;
    }

    int pair[3];
    while (m--){
        fread(pair, sizeof(int), 3, infile);
        Dist[pair[0]][pair[1]] = pair[2];
    }
    fclose(infile);

    cpu_set_t cpu_set;
    sched_getaffinity(0, sizeof(cpu_set), &cpu_set);
    ncpus = CPU_COUNT(&cpu_set);
    count = ceil(n / (double) ncpus);

    pthread_barrier_init(&barr, NULL, (unsigned)ncpus);

    pthread_t threads[ncpus];
    int ID[ncpus];

    for(int t = 0; t < ncpus; t++){
        ID[t] = t;
		pthread_create(&threads[t], NULL, calculate, &ID[t]);
	}

    for(int t = 0; t < ncpus; t++){
		pthread_join(threads[t] , NULL);
	}

    FILE* outfile = fopen(argv[2], "w");
    for (int i = 0; i < n; ++i) {
        fwrite(Dist[i], sizeof(int), n, outfile);
    }
    fclose(outfile);
    return 0;
}