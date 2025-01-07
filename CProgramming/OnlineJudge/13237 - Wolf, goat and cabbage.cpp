#include<bits/stdc++.h>
#include "function.h"
//#include "13237.h"
using namespace std;

void Crossing::solve(){
    State first = {_items[0], _items[1], _items[2], 0, 0, 0, 1};
    queue<list<State>> Q;
    Q.push(list<State>(1, first));

    while(!Q.empty()){
        list<State> cur_path;
        cur_path = Q.front();
        Q.pop();

        State cur = cur_path.back();
        _explored.insert(cur);

        set<State> next = extend(cur);
        for(auto s : next){
            list<State> next_path = cur_path;
            next_path.push_back(s);
            if(found(s)) _solutions.insert(next_path);
            else if(_explored.find(s) == _explored.end()) Q.push(next_path);
            else{
                bool gone = false;
                for(auto pre : cur_path){
                    if(pre == s){
                        gone = true;
                        break;
                    }
                }
                if(!gone) Q.push(next_path);
            }
        }
    }
}
set<State> Crossing::extend(State s){
    set<State> nexts;

    for(int w = 0 ; w <= 1 ; w++){
        for(int g = 0 ; g <= 1 ; g++){
            for(int c = 0 ; c <= 1 ; c++){
                if(w + g + c <= 1){
                    State ss = Go(s, w, g, c);
                    if(valid(ss)) nexts.insert(ss);
                }
            }
        }
    }
    /*State s1 = Go(s, 1, 0, 0);
    if(valid(s1)) nexts.insert(s1);
    State s2 = Go(s, 0, 1, 0);
    if(valid(s2)) nexts.insert(s2);
    State s3 = Go(s, 0, 0, 1);
    if(valid(s3)) nexts.insert(s3);
    State s4 = Go(s, 0, 0, 0);
    if(valid(s4)) nexts.insert(s4);
    */
    return nexts;
}
State Crossing::Go(State s, int wolf, int goat, int cabbage){
    s[0] -= s[6] * wolf;
    s[1] -= s[6] * goat;
    s[2] -= s[6] * cabbage;
    s[3] += s[6] * wolf;
    s[4] += s[6] * goat;
    s[5] += s[6] * cabbage;
    s[6] = -s[6];
    return s;
}
bool Crossing::valid(State s){
    if((s[0] < 0) || (s[1] < 0) || (s[2] < 0) || (s[3] < 0) || (s[4] < 0) || (s[5] < 0)) return false;
    
    if(s[6] == 1){
        if(s[3] > s[4] && s[4] > 0) return false;
        if(s[4] > s[5] && s[5] > 0) return false;
    }
    if(s[6] == -1){
        if(s[0] > s[1]) if(s[1] > 0) return false;
        if(s[1] > s[2]) if(s[2] > 0) return false;
    }
    return true;
}
bool Crossing::found(State s){
    return (s[0] == 0 && s[1] == 0 && s[2] == 0);
}
