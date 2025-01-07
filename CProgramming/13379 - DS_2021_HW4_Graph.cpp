/*Dijkstra Algorithm*/
#include <bits/stdc++.h>
using namespace std;
#define INF 4e9 + 1
#define n 20000 + 1

list<tuple<int, int, bool>> path[n];  //edge

int main(){
    int N, S, E;
    cin >> N >> S >> E;
    int T, B, v, u, w;
    cin >> T;
    for(int i = 0 ; i < T ; i++){
        cin >> v >> u >> w;
        path[v].push_back(make_tuple(u, w, false));
        path[u].push_back(make_tuple(v, w, false));
    }

    cin >> B;
    for(int i = 0 ; i < B ; i++){
        cin >> v >> u >> w;
        path[v].push_back(make_tuple(u, w, true));
        path[u].push_back(make_tuple(v, w, true));
    }

    vector<unsigned int> dist0(n, INF);  //no bridge
    vector<unsigned int> dist1(n, INF);  //one bridge
    dist0[S] = dist1[S] = 0;

    queue<int> Q;
    Q.push(S);

    while(!Q.empty()){
        int spot = Q.front();
        Q.pop();

        for(auto it : path[spot]){
            auto [next_spot, weight, isbridge] = it;
            bool flag = false;
            if(isbridge){
                if(dist1[next_spot] > dist0[spot] + weight){
                    dist1[next_spot] = dist0[spot] + weight;
                    flag = true;
                }
            }else{
                if(dist0[next_spot] > dist0[spot] + weight){
                    dist0[next_spot] = dist0[spot] + weight;
                    flag = true;
                }
                if(dist1[next_spot] > dist1[spot] + weight){
                    dist1[next_spot] = dist1[spot] + weight;
                    flag = true;
                }
            }
            if(flag) Q.push(next_spot);
        }
    }
    cout << min(dist0[E], dist1[E]) << endl;
}
