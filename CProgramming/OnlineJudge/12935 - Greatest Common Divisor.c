#include <stdio.h>
int a,b ;
int ans ;
int main(void){
    scanf("%d %d",&a,&b) ;
    for(int f = 1 ; f <= a && f <= b ; f++){
        if(a % f == 0 && b % f == 0) ans = f ; //common divisor
    }
    printf("%d\n",ans) ;
}
