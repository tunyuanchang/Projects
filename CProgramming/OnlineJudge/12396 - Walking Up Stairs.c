#include<stdio.h>
int N ;
unsigned long long f[117]={} ;
int main(void){
    scanf("%d",&N) ;
    for(int n = 0 ; n <= 116 ; n++){
        if(n > 2) f[n] = f[n-1]+f[n-3] ;
        else f[n]=1 ;
    }
    printf("%llu\n",f[N]) ;
}
