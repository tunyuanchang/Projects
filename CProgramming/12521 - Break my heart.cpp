#include<iostream>
#include<string>
#include<set>
using namespace std;

int main(){
    set<int> s;
    int n, a, l, r;
    cin >> n;
    string cmd;
    while(n--){
        cin >> cmd;
        if(cmd == "insert"){
            cin >> a;
            s.insert(a);
        }
        else if(cmd == "print"){
            int count = 0;
            for(auto i = s.begin(); i != s.end() ; i++, count++){
                cout << *i;
                if(count != s.size() - 1) cout << " ";
                else cout << endl;
            }
        }
        else if(cmd == "min"){
            if(!s.empty()){
                cout << *s.begin() << endl;
            }
        }
        else if(cmd == "range_erase"){
            cin >> l >> r;
            s.erase(s.lower_bound(l), s.upper_bound(r));
        }
    }
}