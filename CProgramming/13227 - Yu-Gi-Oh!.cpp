#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin >> n;
    map<long long, int> map;
    long long a, ace;
    for(int i = 0 ; i < n ; i++){
        cin >> a;
        if(map.find(a) == map.end()) map[a] = 1;
        else map[a]++;

        if(i == 0) ace = a;
        else if(a != ace){
            if(map[a] > map[ace]) ace = a;
            else if(map[a] == map[ace]) if(a > ace) ace = a;
        }
        cout << ace << endl;
    }
}