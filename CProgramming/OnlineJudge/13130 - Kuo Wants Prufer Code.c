#include<stdio.h>
#define max 5005
int n ;
int v[max], u[max], edge[max] ;
int main(){
    scanf("%d",&n) ;
    for(int i=1;i<=n-1;i++){
        scanf("%d%d",v+i,u+i) ;
        edge[v[i]]++, edge[u[i]]++ ;
    }
    for(int t=1;t<=n-2;t++){
        int index, ans ;
        for(index=1;index<=n;index++) if(edge[index]==1) break ;
        for(int i=1, finish=0;i<=n-1 && !finish;i++){
            if(u[i]==index) ans = v[i], finish = 1 ;
            else if(v[i]==index) ans = u[i], finish = 1 ;
            if(finish){
                printf("%d ",ans) ;
                edge[v[i]]--, edge[u[i]]-- ;
                v[i] = u[i] = 0 ;
            }
        }
    }
    printf("\n") ;
}