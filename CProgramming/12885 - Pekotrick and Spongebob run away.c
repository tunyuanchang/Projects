#include<stdio.h>
#define maxn 501
int n, m ;
int k = 1, l = 1; //k number & l times
int x = 1,y = 1 ;
int a[maxn][maxn] ;
int main(){
    scanf("%d%d",&n,&m) ;
    while(k <= n*m){
        while(k <= n*l) a[y++][x]=k++ ; //down
        l++, x++, y-- ;
        while(k <= n*l) a[y--][x]=k++ ; //up
          l++, x++, y++ ;
    }
    //output
    for(int i = 1 ; i <= n ; i++){
        for(int j = 1 ; j <= m ; j++){
            if (j == m) printf("%d\n",a[i][j]) ;
            else printf("%d ",a[i][j]) ;
        }
    }
}
