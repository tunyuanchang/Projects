#include <stdio.h>
int a,b ;
int ans ;
int main(void){
    scanf("%d %d",&a,&b) ;
    for(int f = a * b ; f >= a && f >= b ; f--){
        if(f % a == 0 && f % b == 0) ans = f ; //common multiple
    }
    printf("%d\n",ans) ;
}
