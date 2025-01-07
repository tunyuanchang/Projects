#include<stdio.h>
#define max(a,b) (((a)>(b)) ?(a) :(b))
int q,ans,i ;
int arr[63] ;
unsigned long long n ;
void solve(int ) ;
int main(){
    scanf("%d",&q) ;
    while(q--){
        for(int j=0;j<63;j++) arr[j]=0 ;
        ans=-1,i=0 ;
        scanf("%llu",&n) ;
        solve(0) ;
        if(i<2) printf("-1\n") ;
        else printf("%d\n",ans-1) ;
    }
}
void solve(int index){
    if((n>>index)<1){
        if(i>=2)
            for(int k=0;k<i-1;k++)
                ans=max(ans,arr[k+1]-arr[k]) ;
        return ;
    }
    if((n>>index) & 1) arr[i]=index,i++ ;
    solve(index+1) ;
}
