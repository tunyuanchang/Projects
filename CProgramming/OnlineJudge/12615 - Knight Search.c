#include<stdio.h>
int n,available = 0 ;
int x[8]={2,2,-2,-2,1,1,-1,-1} ;
int y[8]={1,-1,1,-1,2,-2,2,-2} ;
char board[101][101] ;
char str[10] = "ICPCASIASG" ;
void solve(int r,int c,int index){
    if(index == 10){
        available = 1 ;
        return ;
    }
    for(int i=0;i<8;i++){
        int R = r + y[i], C = c + x[i] ;
        if(R>=1 && R<=n && C>=1 && C<=n){
            if(board[R][C] == str[index]) solve(R,C,index+1) ;
        }
    }
}
int main(){
    scanf("%d\n",&n) ;
    for(int i=1;i<=n;i++) fgets(board[i]+1,n+1,stdin) ;
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++)
        if(board[i][j] == str[0] && !available) solve(i,j,1) ;
    available==1 ?printf("YES\n") :printf("NO\n") ;
}
