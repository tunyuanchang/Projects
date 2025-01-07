#include<stdio.h>
#define maxn 101
int N ; 
long long ans ;
int count[maxn][maxn] = {0} ;
int main(void){
    scanf("%d",&N);
    for(int i = 2 ; i <= N ; i++){
        int k = i, f=2;  //f factor
        while (k >= 2 && f <= N){ //find factor
            while(k % f == 0){
                count[i][f]++ ;
                k /= f ; }
            f++ ;
        }
    }
    long long ans = 1 ;
    for(int f = 2 ; f <= N ; f++){
        for(int i = 2 ; i <= N ; i++){
            count[0][f] += count[i][f] ; //count factor number
        }
        ans *= (count[0][f] + 1) ;
    }
    printf("%lld",ans) ;
}
