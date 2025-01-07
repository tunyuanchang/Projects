#include<stdio.h>
#include<math.h>
int n ;
int solve(int ) ;
int main(){
    scanf("%d",&n) ;
    printf("%d\n",solve(n/2)) ;
}
int solve(int i){ //do front i groups
    if(i==0) return 1 ;
    int ans = 0 ;
    ans = 3*solve(i-1) ;
    for(int k=i-2;k>=0;k--){
        ans += 2*solve(k) ;
    }
    return ans ;
}
