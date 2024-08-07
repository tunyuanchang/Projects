#include <assert.h>
#include <iostream>
#include <math.h>
#include <omp.h>

int main(int argc, char** argv) {
	if (argc != 3) {
		fprintf(stderr, "must provide exactly 2 arguments!\n");
		return 1;
	}
	unsigned long long r = atoll(argv[1]);
	unsigned long long k = atoll(argv[2]);
	unsigned long long sum = 0;

#pragma omp parallel for schedule(static, 30) reduction(+: sum)
      		for (unsigned long long x = 0; x < r; x++) {
      			unsigned long long y = ceil(sqrtl(r*r - x*x));
      			sum += y;
      			if(x%30 == 0) sum %= k;
      		} 

    std::cout << (4*sum) % k << std::endl;
    return 0;
}
