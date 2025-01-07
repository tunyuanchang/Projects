#include <bits/stdc++.h>
#include "function.h"
using namespace std;

int n, k, q;

int main() {
	cin >> n >> k >> q;
	KuoYangPresent present = KuoYangPresent(k);
	for (int i = 1; i <= n; ++ i) {
		int x;
		cin >> x;
		present.Push(x);
	}
	while (q--) {
		string op;
		cin >> op;
		if (op == "push") {
			int x;
			cin >> x;
			present.Push(x);
		}
		else if (op == "pop") {
			present.Pop();
		}
		else {
			cin >> op;
			present.ProgrammingTanoshi();
		}
	}
	present.KuoYangTeTe();
	present.PrintList();
}
