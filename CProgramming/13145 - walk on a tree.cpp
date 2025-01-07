#include<bits/stdc++.h>
using namespace std;

int edge[505][505] = {0};
int path[505][505] = {0};
int oneedge[505][505] = {0};

int main(){
    int n, q;
    cin >> n >> q;
    for(int i = 0 ; i < n - 1 ; i++){
        int u, v, x;
        cin >> u >> v >> x;
        edge[u][v] = edge[v][u] = 1;
        path[u][v] = path[v][u] = 1;
        oneedge[u][v] = oneedge[v][u] = x;
    }
    for(int i = 0 ; i < 2 ; i++){
        for(int x = 0 ; x < 501 ; x++){
            for(int y = 0 ; y < 501 ; y++){
                if(edge[x][y] == 1){
                    for(int z = 0 ; z < 501 ; z++){
                        if(edge[y][z] == 1 && z != x){
                            if(edge[x][z] == 0){
                                edge[x][z] = edge[z][x] = 1;
                                path[x][z] = path[z][x] = path[x][y] + path[y][z];
                                oneedge[x][z] = oneedge[z][x] = oneedge[x][y] + oneedge[y][z];
                            }
                            else{
                                if(path[x][y] + path[y][z] < path[x][z]){
                                    path[x][z] = path[z][x] = path[x][y] + path[y][z];
                                    oneedge[x][z] = oneedge[z][x] = oneedge[x][y] + oneedge[y][z];
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    for(int i = 0 ; i < q ; i++){
        int k, m;
        cin >> k >> m;
        int pre, cur;
        int count = 0;
        for(int i = 0 ; i < k ; i++){
            if(i == 0) cin >> cur;
            else{
                pre = cur;
                cin >> cur;
                count += oneedge[pre][cur];
            }
        }
        cout << ((count >= m) ? "YES" : "NO") << endl;
    }
}