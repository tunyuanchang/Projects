#include <stdio.h>
#include "function.h"

int main() {
	int n;
	scanf("%d\n", &n);
	Monkey* arr = CreateMonkeyArray(n);
	for(int i = 0; i < n; i++) {
		int num;
		char c[51];
		scanf("%d %s", &num, c);
		SetVal(arr, i, num, c);
	}
	for(int i = 0; i < n; i++) {
		for(int j = i + 1; j < n; j++) {
			if(Compare(arr, i, j) > 0) {
				Swap(arr, i, j);
			}
		}
	}
	for(int i = 0; i < n; i++) {
		printf("%d %s\n", arr[i].num, arr[i].name);
	}
	FreeMonkeyArray(arr, n);
}
