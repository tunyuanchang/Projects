#include<stdio.h>
#define maxn 100001
#define max 10001
long int n,count[max] ;
long long ans ;
int a[maxn];
int main(void){
    scanf("%ld",&n) ;
    for(long int i = 0 ; i < n ; i++){
        scanf("%d",&a[i]) ;
        count[a[i]]++ ; //count repeat
    }
    for(int i = 0 ; i < max ; i++){
        if(count[i] >= 2) ans += count[i] * (count[i] - 1) / 2 ; //pair = n*(n-1)/2
    }
    printf("%lld\n",ans) ;
}
