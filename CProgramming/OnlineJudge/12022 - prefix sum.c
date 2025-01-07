#include<stdio.h>
#define maxn 1000001
long int n,m ;
long int p,q ;
long int a[2][maxn] ;
int main(void){
    scanf("%ld",&n) ;
    for(long int i = 1 ; i <= n ; i++){
        scanf("%ld",&a[0][i]) ;
        a[1][i] = a[1][i-1] + a[0][i] ; //prefix
    }
    scanf("%ld",&m) ;
    while(m--){
        scanf("%ld %ld",&p,&q) ;
        printf("%ld\n",a[1][q] - a[1][p-1]) ;  //sum ap~aq
    }
}
