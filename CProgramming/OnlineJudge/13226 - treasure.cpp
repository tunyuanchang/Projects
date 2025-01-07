#include<bits/stdc++.h>
using namespace std;

int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};
int main(){
    int k;
    cin >> k;
    int n, m;
    cin >> n >> m;
    int map[n][m] = {0};
    int start;
    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < m ; j++){
            cin >> map[i][j];
            if(map[i][j] == 2021) start = i * n + j;
        }
    }
    int ans = -1, goal = 1;

    queue<pair<int, int>> Q; //pos steps
    set<int> explored;

    Q.push(make_pair(start, 0));
    explored.insert(start);

    while(!Q.empty()){
        auto [pos, steps] = Q.front();
        Q.pop();
        int y = pos / n;
        int x = pos % n;

        if(map[y][x] == goal){
            if(goal == k){
                ans = steps;
                break;
            }
            explored.clear();
            queue<pair<int, int>> newQ;
            newQ.push(make_pair(pos, steps));
            goal++;
            Q = newQ;
            continue;
        }

        for(int i = 0 ; i < 4 ; i++){
            y = pos / n + dy[i];
            x = pos % n + dx[i];
            if(y >= 0 && y < n && x >= 0 && x < m && map[y][x] != -1){
                if(explored.find(y * n + x) == explored.end()){
                    Q.push(make_pair(y * n + x, steps + 1));
                    explored.insert(y * n + x);
                }
            }
        }
    }
    cout << ans <<endl;
}