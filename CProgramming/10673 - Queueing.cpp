#include<bits/stdc++.h>
using namespace std;

int main(){
    queue<string> name;
    string op, n;
    while(cin >> op){
        if(op == "Push"){
            cin >> n;
            name.push(n);
        }
        else if(op == "Pop"){
            if(!name.empty()) name.pop();
        }
        else if(op == "Front"){
            if(!name.empty()) cout << name.front() << endl;
            else cout << "empty" << endl;
        }
    }
}
