#include <iostream>
#include <cstring>
#include "function.h"
using namespace std;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int N, Q, Fee, U;
	Casino *casino = new Casino();

	cin >> N;
	while (N--) {
		string op;
		cin >> op >> Q >> Fee >> U;
		casino->Enterance(Fee, U);
		while (Q--) {
			cin >> op;
			if (op == "Guest") {
				string name;
				int money, skill;
				cin >> name >> money >> skill;
				casino->Guest(name, money, skill);
			}
			else if (op == "Twenty") {
				cin >> op;
				casino->TwentyOne();	
			}
		}
		casino->EndDay();
	}
	casino->Result();
}
