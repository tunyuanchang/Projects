#include <bits/stdc++.h>
#include "function.h"
//#include "11495.h"

using namespace std;

void Crossing::solve(){
    State first = {_npeople[0], _npeople[1], 0, 0, 1};
    queue<list<State>> tasks;
    map<State, list<State>> sol;
    tasks.push(list<State>(1, first));  //count state
    while(!tasks.empty()){
        list<State> cur_path, next_path;
        set<State> nextstates;
        State cur_state;
        cur_path = tasks.front();
        tasks.pop();

        cur_state = *cur_path.rbegin();
        _explored.insert(cur_state);

        nextstates = extend(cur_state);
        for(auto state : nextstates){
            if(_explored.find(state) != _explored.end())
                continue;
            next_path = cur_path;
            next_path.push_back(state);
            if(found(state)) _solutions.insert(next_path);
            else tasks.push(next_path);
        }
    }
}
set<State> Crossing::extend(State s){
    set<State> nextstates;
    for(int m = 0 ; m <= 2 ; m++){
        for(int c = 0 ; c <= 2 ; c++){
            if(m + c >= 1 && m + c <= 2){
                State next_state = Go(s, m, c);
                if(valid(next_state)) nextstates.insert(next_state);
            }
        }
    }
    return nextstates;
}
State Crossing::Go(State s, int missionary, int cannibal){
    s[0] -= s[4] * missionary;
    s[1] -= s[4] * cannibal;
    s[2] += s[4] * missionary;
    s[3] += s[4] * cannibal;
    s[4] = -s[4];
    return s;
}
bool Crossing::valid(State s){
    if(s[0] < 0 || s[1] < 0 || s[2] < 0 || s[3] < 0) return false;
    return ((s[0] == 0 || s[0] >= s[1]) && (s[2] == 0 || s[2] >= s[3]));
}
bool Crossing::found(State s){
    return (s[0] == 0 && s[1] == 0);
}