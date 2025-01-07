#include<stdio.h>
#include<math.h>
int n,w ; //w total weight
long long ans ;
int a[20] ; //weight
long long b[20],value[1001] ; //value
int main(){
    scanf("%d%d",&n,&w) ;
    for(int i=0;i<n;i++) scanf("%d %lld",&a[i],&b[i]) ;
    for(int i=0;i<n;i++){
        for(int j=w;j<=0;j--){
            if(j-a[i]>=0){
                if(value[j]<value[j-a[i]]+b[i])
                    value[j]=value[j-a[i]]+b[i] ;
            }
        }
    }
    for(int i=0;i<=w;i++){
        if(ans<value[i]) ans=value[i] ;
    }
    printf("%lld\n",ans) ;
}
