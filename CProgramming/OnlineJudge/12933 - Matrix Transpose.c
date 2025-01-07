#include<stdio.h>
#define maxn 1001
int r,c ;
int a[maxn][maxn], b[maxn][maxn] ;
int main(void){
    scanf("%d %d",&r,&c);
    for(int i = 1 ; i <= r ; i++){
        for(int j = 1 ; j <= c ; j++)
            scanf("%d",&a[i][j]);
    }
    for(int i = 1 ; i <= c ; i++){
        for(int j = 1 ; j <= r ; j++){
            b[i][j] = a[j][i] ;
            if (j == r) printf("%d\n",b[i][j]) ;
            else printf("%d ",b[i][j]) ;
        }
    }
}
