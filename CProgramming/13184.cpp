#include <iostream>
#include <string>
#include "function.h"
using namespace std;

int n;
Casino casino = {};

int main() {
	cin >> n;
	for (int i = 0; i < n; ++ i) {
		string op;
		int q;
		
		cin >> op >> q;
		for (int j = 0; j < q; ++ j) {
			cin >> op;
			if (op == "Guest") {
				string name; 
				int money, skill;
				cin >> name >> money >> skill;
				casino.GuestEnter(name, money, skill);
			} 
			else if (op == "Win") {
				string name;
				int money;
				cin >> name >> money;
				casino.Win(name, money);
			}
		}
		casino.EndDay();
	}
	casino.Result();
}
