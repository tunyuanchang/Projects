#include <bits/stdc++.h>
#include<iomanip>
using namespace std;

list<pair<int, double> > path[501];

int main(){
    int n, m, r;
    cin >> n >> m >> r;
    int a, b;
    double p;
    for(int i = 0 ; i < m ; i++){
        cin >> a >> b >> p;
        path[a].push_back(make_pair(b, p));
        path[b].push_back(make_pair(a, p));
    }

    int S, E;

    for(int i = 0 ; i < r ; i++){
        cin >> S >> E;

        vector<double> probability(501, 0.0);
        probability[S] = 1.0;

        queue<int> Q;
        Q.push(S);

        while(!Q.empty()){
            int now = Q.front();
            Q.pop();

            for(auto it : path[now]){
                auto [next, P] = it;
                if(probability[next] < probability[now] * P){
                    probability[next] = probability[now] * P;
                    Q.push(next);
                }
            }
        }
        
        cout << fixed << setprecision(5) << probability[E] << endl;
    }
}
