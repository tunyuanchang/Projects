#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "function.h"

int main() {
	int len;
	int **ans;
	
	scanf("%d", &len);
	
	int *a = (int*)malloc(len * sizeof(int));

	for (int i = 0;i < len;i++) {
		scanf("%d", &a[i]);
	}

	ans = s(a,len);

	for (int i = 0;i < (int)sqrt(len);i++) {
		for (int j = 0;j < (int)sqrt(len);j++) {
			printf("%d", ans[i][j]);
		}
		printf("\n");
	}
	
	free(a);
	return 0;
}
