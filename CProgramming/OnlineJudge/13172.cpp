#include<iostream>
#include "function.h"
using namespace std;
int main(){
    int x, n, m;
    string s;
    cin >> x >> n >> m >> s;
    special_power sp(n);
    cout << sp.fpow(x) << "\n";
    cout << sp.fpow(x, m) << "\n";
    cout << sp.fpow() << "\n";
    cout << sp.fpow(s) << "\n";
    cout << sp.fpow(s, m) << "\n";
}
