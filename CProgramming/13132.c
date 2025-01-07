#include <stdio.h>
#include "function.h"

void PrintList();

int main() {
	scanf("%d %d %d", &n, &k, &q);
	for (int i = 1; i <= n; ++ i) {
		int x;
		scanf("%d", &x);
		push(x);
	}
	while (q--) {
		char op[20];
		scanf("%s", op);
		if (op[1] == 'u') {
			int x;
			scanf("%d", &x);
			push(x);
		}
		else if (op[1] == 'o') {
			pop();
		}
		else {
			scanf(" %s", op);
			programming_tanoshi();
		}
	}
	KuoYangTeTe();
	PrintList();
}

void PrintList() {
	Node* res = head;
	while (res) {
		printf("%d ", res->val);
		res = res->next;
	}
	puts("");
}
