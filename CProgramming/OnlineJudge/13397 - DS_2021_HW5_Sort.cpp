#include<bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
	
    int n, a;
    stack<int> A;
    while(cin >> n){
        for(int i = 0 ; i < n ; i++){
            cin >> a;
            if(A.empty() || abs(a) < abs(A.top()) || a == A.top()) A.push(a);
            else{
                while(!A.empty()){
                    if(abs(a) >= abs(A.top())){
                        cout << A.top() << ' ';
                        A.pop();
                    }else break;
                }
                cout << a;
                if(i != n - 1 || !A.empty()) cout << ' ';
            }
        }
        while(!A.empty()){
            cout << A.top();
            if(A.size() != 1) cout << ' ';
            A.pop();
        }
        cout << endl;
    }
}
