#include<stdio.h>
#define maxn 101 //include 100
int n,m,q;
int u,d,l,r;
int ans;
int a[maxn][maxn] ;
int main(){
    //input
    scanf("%d %d",&n,&m);
    for(int i = 1 ; i <= n ; i++){
        for(int j = 1 ; j <= m ; j++){
            scanf("%d",&a[i][j]);
        }
    }
    scanf("%d",&q);
    for(int t = 0 ; t < q ; t++) {
        scanf("%d %d %d %d",&u,&d,&l,&r);
        ans = 0 ;
        for(int i = u ; i <= d ; i++){
            for(int j = l ; j <= r ; j++){
                if (a[i][j] > ans) ans=a[i][j];  //find max
            }
        }
        printf("%d\n",ans);
    }
}
