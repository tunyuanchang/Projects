#include<stdio.h>
#include<math.h>
/*
a * b + a + b = a * 10^(len(b)) + b
=> a * (b+1) = a * 10^(len(b))
=> b = 10^(len(b)) - 1
 : {(a,b) | a any integer , b = 9,99,999...}
*/
int t ;
long long a,b ;
int main(){
    scanf("%d",&t) ;
    while(t--){
        scanf("%lld%lld",&a,&b) ;
        printf("%lld\n",a*(long long)log10(b+1)) ;
        //printf("%.0f\n",a*floor(log10(b+1))) ;
    }
}
