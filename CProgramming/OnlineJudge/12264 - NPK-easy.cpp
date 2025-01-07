#include <bits/stdc++.h>
using namespace std;

int main(){
    int n, a;
    bool flag;  //insert
    string cmd;
    deque<queue<int>> line;
    cin >> n;
    while(n--){
        cin >> cmd;
        if(cmd == "ENQUEUE"){
            flag = false;
            cin >> a;
            for(auto it = line.begin() ; it != line.end() ; it++){
                if (it->front() % 3 == a % 3){
                    it->push(a);
                    flag = true;
                    break;
                }
            }
            if(!flag){
                queue<int> q;
                q.push(a);
                line.push_back(q);
            }
        }
        else if (cmd == "DEQUEUE"){
            if(!line.empty()){
                cout << line.begin()->front() << endl;
                line.begin()->pop();
                if(line.begin()->empty()) line.pop_front();
            }
        }
    }
}