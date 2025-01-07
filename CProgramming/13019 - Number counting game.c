#include<stdio.h>
#define max 1024*1024+5 //2^20
int N,K ;
int use[max] ; //binary mark select
int solve(int,int) ;
int main(){
    int q ;
    scanf("%d",&q) ;
    while(q--){
        scanf("%d%d",&N,&K) ;
        for(int i=0;i<(1<<N);i++) use[i]=0 ; //reset
        if(solve(0,0)==1) printf("True\n") ;
        else printf("False\n") ;
    }
}
int solve(int select,int sum){
    if(sum>=K) return use[select]=-1 ; //lose
    if(use[select]!=0) return use[select] ;
    int next ; //next player
    for(int i=0;i<N;i++){
        if((select&(1<<i))==0){ //not select same
            next=solve(select|(1<<i),sum+(i+1)) ;
            if(next==-1) return use[select]=1 ; //all lose
        }
    }
    return use[select]=-1 ;
}
