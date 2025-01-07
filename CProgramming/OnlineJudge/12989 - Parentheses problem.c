#include<stdio.h>
#include<math.h>
int n,a[105] ;
char s[105] ;
long long ans=0 ;
int main(){
    scanf("%d",&n) ;
    scanf("%s",s+1) ;
    for(int i=1; i<=n;i++){ //count layer
        if(s[i]=='(') a[i]=a[i-1] + 1 ;
        else a[i]=a[i-1] - 1 ;
    }
    for(int i=1;i<=n;i++){
        if(s[i]=='(' && s[i+1]==')') // () -> 1
            ans +=pow(2,a[i-1]) ;
    }
    printf("%lld\n",ans) ;
}
