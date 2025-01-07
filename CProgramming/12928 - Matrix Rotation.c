#include<stdio.h>
#define maxn 101
int n,m ; //n row m column
long int a[maxn][maxn], ans[maxn][maxn] ;
long int t ;
int main(void){
    scanf("%d %d",&n,&m) ;
    for(int i = 0 ; i < n ; i++)
        for(int j = 0 ; j < m ; j++)
            scanf("%ld",&a[i][j]) ;
    scanf("%ld",&t) ;
    t %= 4 ;
    int r = n, c = m ;
    while(t--){ //clockwise 90 per time
        r = c, c = n + m - r ;
        for(int i = 0 ; i < r ; i++)
            for(int j = 0 ; j < c ; j++)
                ans[i][j] = a[c-1-j][i] ; //rotate
        for(int i = 0 ; i < r ; i++)
            for(int j = 0 ; j < c ; j++)
                a[i][j] = ans[i][j] ; //copy
    }
    for(int i = 0 ; i < r ; i++)
        for(int j = 0 ; j < c ; j++)
            if (j == c - 1) printf("%ld\n",a[i][j]) ;
            else printf("%ld ",a[i][j]) ;
}
