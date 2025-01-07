#include<bits/stdc++.h>
using namespace std;

int main(){
    int L, HP, MHP, MDMG;
    cin >> L >> HP >> MHP >> MDMG;
    vector<int> DMG, HL;
    DMG.push_back(0);
    HL.push_back(0);
    for(int i = 0 ; i < L ; i++){
        int dmgi, hli;
        cin >> dmgi >> hli;
        DMG.push_back(dmgi);
        HL.push_back(hli);
    }
    int ans = -1;
    queue<tuple<int, int, int, int>> task;  //lv hp mhp steps
    set<tuple<int, int, int>> state;  //lv hp mhp
    task.push(make_tuple(1, HP, MHP, 0));
    while(!task.empty()){
        auto [lv, hp, mhp, steps] = task.front();
        task.pop();
        //Win
        if(mhp <= 0){
            ans = steps;
            break;
        }
        //Lose
        if(hp <= 0) continue;

        //BFS check
        if(state.find(make_tuple(lv, hp, mhp)) != state.end()) continue;
        state.insert(make_tuple(lv, hp, mhp));
        //ATTACK
        task.push(make_tuple(lv, hp - MDMG, mhp - DMG[lv], steps + 1));
        //HEAL
        if(hp + HL[lv] <= HP)
            task.push(make_tuple(lv, hp + HL[lv] - MDMG, mhp, steps + 1));
        else if(hp + HL[lv] > HP)
            task.push(make_tuple(lv, HP - MDMG, mhp, steps + 1));
        //Level-up
        if(lv < L)
            task.push(make_tuple(lv + 1, hp - MDMG, mhp, steps + 1));
    }
    cout << ans << endl;
}