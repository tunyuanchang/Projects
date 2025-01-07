#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

int main(){
    vector<int> max_heap;
    int k;
    string cmd;
    while(cin >> cmd){
        if(cmd == "PUSH"){
            cin >> k;
            max_heap.push_back(k);
            push_heap(max_heap.begin(), max_heap.end());
        }
        else if(cmd == "POP"){
            if(!max_heap.empty()){
                pop_heap(max_heap.begin(), max_heap.end());
                max_heap.pop_back();
            }
        }
        else if(cmd == "TOP"){
            if(max_heap.empty()) cout << "Null" << endl;
            else cout << *max_heap.begin() << endl;
        }
    }
}