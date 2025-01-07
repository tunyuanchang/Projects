#include <bits/stdc++.h>
using namespace std;

// G[i] is the neighbor towns of town i
vector<int> G[100005];
int Dist[100005];

int main() {
    int N, M, K;
    cin >> N >> M >> K;
    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
    }
    
    queue<pair<int, int>> Q; //id dist
    fill(Dist, Dist+100005, -1);

    for (int i = 0; i < K; i++) {
        int x;
        cin >> x;
        Q.push(make_pair(x, 0));
    }
    
    // [TODO] complete the task!

    while(!Q.empty()){
        auto [ID, D] = Q.front();
        Q.pop();
        
        if(Dist[ID] != -1) continue;
        Dist[ID] = D;

        for(auto townid : G[ID]){
            if(Dist[townid] != -1) continue;
            Q.push(make_pair(townid, D + 1));
        }
    }

    // Output
    for (int i = 1; i <= N; i++) {
        cout << Dist[i] << '\n';
    }
    return 0;
}