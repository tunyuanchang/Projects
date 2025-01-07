#include<stdio.h>

#define max 505

int n, q, u, v, x, k, m, a1, a2;
int edge[max][max], path[max][max], oneedge[max][max];

int main(){
    scanf("%d%d",&n,&q);
    for(int i = 0 ; i < n ; i++)
        for(int  j = 0 ; j < n ; j++)
            path[i][j] = 0x7ffffff;
    for(int i = 0 ; i < n-1 ; i++){
        scanf("%d%d%d",&u,&v,&x) ;
        edge[u][v] = edge[v][u] = 1;
        path[u][v] = path[v][u] = 1;
        oneedge[u][v] = oneedge[v][u] = x;
    }
    for(int t = 0 ; t < 2 ; t++){
        for(int X = 0 ; X < n ; X++){
            for(int Y = 0 ; Y < n ; Y++){
                if(path[X][Y]){
                    for(int Z = 0 ; Z < n ; Z++){
                        if(Z != X && path[X][Z] > path[X][Y] + path[Y][Z]){
                            path[X][Z] = path[Z][X] = path[X][Y] + path[Y][Z];
                            oneedge[X][Z] = oneedge[Z][X] = oneedge[X][Y] + oneedge[Y][Z];
                        }
                   }
                }
            }
        }
    }

    while(q--){
        int ans = 0;
        scanf("%d%d",&k,&m);
        for(int i = 0 ; i < k ; i++){
            a1 = a2;
            scanf("%d",&a2);
            if(i != 0) ans += oneedge[a1][a2];
        }
        if(ans >= m) printf("YES\n");
        else printf("NO\n");
    }
}