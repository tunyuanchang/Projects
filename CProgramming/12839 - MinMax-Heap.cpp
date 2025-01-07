#include<iostream>
#include<set>
using namespace std;

int main(){
    multiset<int> ms;
    int a;
    string cmd;
    while(cin >> cmd){
        if(cmd == "PUSH"){
            cin >> a;
            ms.insert(a);
        }
        else if(cmd == "POPMIN"){
            if(!ms.empty()) ms.erase(ms.begin());
        }
        else if(cmd == "POPMAX"){
            if(!ms.empty()) ms.erase(ms.find(*ms.rbegin()));
        }
        else if(cmd == "MIN"){
            if(!ms.empty()) cout << *ms.begin() << endl;
            else cout << "Null\n";
        }
        else if(cmd == "MAX"){
            if(!ms.empty()) cout << *ms.rbegin() << endl;
            else cout << "Null\n";
        }
        else if(cmd == "CLEAR"){
            ms.clear();
        }
    }
}