#include<stdio.h>
int q,r,c ;
int sr,sc ; //start row & start column
long long count,step ; //count-all the number of paths & step-shortest step count
int x[4]={0,0,-1,1}, y[4]={-1,1,0,0} ;
int use[105][105] ;
char maze[105][105] ;
void solve(int,int,long long) ;
int main(){
    scanf("%d",&q) ;
    while(q--){
        //reset
        count = 0 ;step = 1e8 ;
        scanf("%d%d",&r,&c) ;
        for(int i=1;i<=r;i++){
            scanf("%s",maze[i]+1) ;
            for(int j=1;j<=c;j++)
               if(maze[i][j]=='S') sr=i ,sc=j ;
        }
        solve(sr,sc,0) ;
        if(count>0) printf("%lld %lld\n",count,step) ;
        else printf("0 -1\n") ;
    }
}
void solve(int R,int C,long long num){
    if(maze[R][C]=='F'){
        count++ ;
        if(num<step) step = num ;
        return ;
    }
    for(int i=0;i<4;i++)
        if(maze[R+y[i]][C+x[i]]=='$' || maze[R+y[i]][C+x[i]]=='F'){
            if(!use[R+y[i]][C+x[i]]){
                use[R+y[i]][C+x[i]]=1 ;
                solve(R+y[i],C+x[i],num+1) ;
                use[R+y[i]][C+x[i]]=0 ;
            }
        }
}

