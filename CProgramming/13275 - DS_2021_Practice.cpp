#include<bits/stdc++.h>
using namespace std;

int main(){
    int n, a, index, l, r;
    cin >> n;
    int arr[n] = {0};
    for(int i = 0 ; i < n ; i++) cin >> arr[i];
    while(cin >> a){
        l = 0, r = n;
        while(true){
            index = (l + r) / 2;
            if(a > arr[index]) l = index;
            else if(a < arr[index]) r = index;
            else break;
        }
        cout << index << endl;
    }
}
