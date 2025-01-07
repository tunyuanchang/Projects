#include <stdio.h>
#include <stdlib.h>
#include "function.h"
#define maxn 100005
int arr[maxn];
int main() {
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&arr[i]);
	qsort(arr+1, n, sizeof(int),cmp);
	for(int i=1;i<=n;i++) {
		if(i != 1) printf(" ");
		printf("%d",arr[i]);
	}
	printf("\n");
	return 0;
}
