#include <stdio.h>
#include <stdlib.h>
#include "function.h"

int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		int n;
		scanf("%d\n", &n);
		Monkey* arr = CreateMonkeyArray(n);
		for(int i = 0; i < n; i++) {
			int num;
			char* c = (char*) malloc(sizeof(char) * 100001);
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
}
