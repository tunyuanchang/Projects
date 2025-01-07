#include<stdio.h>
int n,q,a,b ;
long long arr[30][30],ans=0 ;
long long m, w[30],v[30] ;
void solve(int ,long long ,long long) ;
int main(){
    ans=0 ;
    scanf("%d%lld",&n,&m) ;
    for(int i=0;i<n;i++) scanf("%lld %lld",&w[i],&v[i]) ;
    scanf("%d",&q) ;
    while(q--){
        ans=0 ;
        scanf("%d%d",&a,&b) ;
        if(arr[a][b]) printf("%lld\n",arr[a][b]) ;
        else {
            if(w[a-1]+w[b-1]<=m) solve(0,w[a-1]+w[b-1],v[a-1]+v[b-1]) ;
            arr[a][b]=ans ;
            printf("%lld\n",ans) ;
        }
    }
}
void solve(int i,long long weight,long long value){
    if(i==n){
        if(ans<value) ans=value ;
        return ;
    }
    if(i==a-1 || i==b-1) solve(i+1,weight,value) ;
    else{
        for(int j=0;j<2;j++){
            if(j==0){ //not choose
                solve(i+1,weight,value) ;
            }
            else{ //choose
                if(weight+w[i]>m) return ;
                else solve(i+1,weight+w[i],value+v[i]) ;
            }
        }
    }
}
