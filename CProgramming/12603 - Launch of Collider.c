#include<stdio.h>
#define min(a,b) (((a)<(b)) ?(a) :(b))
int n, cur, prev ;
char dir[200005] ;
int main(){
    int mintime = 1e9 ;
    scanf("%d\n%s",&n,dir) ;
    for(int i=0;i<n;i++){
        prev = cur ;
        scanf("%d",&cur) ;
        if(i==0) continue ;
        if(dir[i]=='L' && dir[i-1]=='R') mintime = min(mintime,(cur-prev)/2) ;
    }
    if(mintime==1e9) printf("-1\n") ;
    else printf("%d\n",mintime) ;
}
