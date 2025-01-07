#include<stdio.h>
#include<stdlib.h>
int n,ans ;
int xi[200005] ;
int cmp(const void* a,const void* b){
    int x = *(int*)a,y = *(int*)b ;
    if(x>y) return 1 ;
    if(x==y) return 0 ;
    if(x<y) return -1 ;
}
int main(){
    scanf("%d",&n) ;
    for(int i=0;i<=n;i++) scanf("%d",&xi[i]) ;
    qsort(xi+1,n,sizeof(int),cmp) ;
    if(xi[0]<xi[1]) ans = 2 * ( xi[n] - xi[0] ) ;
    else if(xi[0]>xi[n]) ans = 2 * ( xi[0] - xi[1] ) ;
    else ans = 2 * ( xi[n] - xi[1] ) ;
    printf("%d\n",ans) ;
}
