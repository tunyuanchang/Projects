#include <stdio.h>
#include "function.h"

int main() {
	char op[20];
	while (scanf("%s", op) != EOF) {
		if (op[1] == 'U') {
			int x;
			scanf("%d", &x);
			push(x);
		}
		else if (op[1] == 'O') {
			pop();
		}
		else if (op[1] == 'R') {
			int k;
			scanf("%s %d", op, &k);
			programming_tanoshi(k);
		}
		else if (op[1] == 'P') {
			scanf("%s", op);
			IP2_sugoi();
		}
	}
	KuoYangTeTe();
	
	while (head != NULL) {
		printf("%d ", head->val);
		head = head->next;
	}
	puts("");
	return 0;
}
