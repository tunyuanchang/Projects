#include<stdio.h>
int n,m,ans = 0 ;  //game bill
int c[1000], a[1000] ;  //cost value
int main(){
    scanf("%d %d",&n,&m) ;
    for(int i=0;i<n;i++) scanf("%d",&c[i]) ;
    for(int i=0;i<m;i++) scanf("%d",&a[i]) ;
    for(int i=0,j=0;i<n && j<m;i++)
        if(c[i]<=a[j]) ans++, j++ ;
    printf("%d\n",ans) ;
}
