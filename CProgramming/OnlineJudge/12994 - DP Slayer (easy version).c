#include<stdio.h>
int n,q,a,b ;
long long ans=0 ;
long long m, w[20],v[20] ;
void problem(int ,long long ,long long) ;
int main(){
    ans=0 ;
    scanf("%d%lld",&n,&m) ;
    for(int i=0;i<n;i++) scanf("%lld %lld",&w[i],&v[i]) ;
    scanf("%d",&q) ;
    while(q--){
        ans=0 ;
        scanf("%d%d",&a,&b) ;
        problem(0,0,0) ;
        printf("%lld\n",ans) ;
    }

}
void problem(int i,long long weight,long long value){
    if(i==n){
        if(ans<value) ans=value ;
        return ;
    }
    for(int j=0;j<2;j++){
        if(j==0){ //not choose
            problem(i+1,weight,value) ;
        }
        else{ //choose
            if(weight+w[i]>m) return ;
            else problem(i+1,weight+w[i],value+v[i]) ;
        }
    }
}
