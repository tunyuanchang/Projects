#include<bits/stdc++.h>
using namespace std;

vector<int> node[1001];

int main(){
    int n, a, b;
    
    while(cin >> n){
        if(n == 0) break;
        int count = 0, root;
        for(int i = 0 ; i < 1001 ; i++) node[i].clear();

        for(int i = 0 ; i < n ; i++){
            cin >> a >> b;
            node[a].push_back(b);
        }
        cin >> root;

        queue<int> Q;
        Q.push(root);

        while(!Q.empty()){
            int now = Q.front();
            Q.pop();
            
            if(node[now].empty()){
                count++;
                continue;
            }

            for(auto next : node[now]){
                Q.push(next);
            }
        }

        cout << count << endl;
    }
}