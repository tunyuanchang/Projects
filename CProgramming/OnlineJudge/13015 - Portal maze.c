#include <stdio.h>
#include <ctype.h>
int t,r,c ;
int port_r[26],port_c[26] ; //port row & port column
int x[4]={0,0,-1,1}, y[4]={-1,1,0,0} ;
int bfs[302][302] ;
char maze[302][302] ;
void solve(int,int) ;
int main(){
    int sr,sc ; //start row & start column
    int er,ec ; //end row & end column
    scanf("%d",&t) ;
    while(t--){
        //reset
        for(int i=0;i<302;i++)
            for(int j=0;j<302;j++)
                bfs[i][j]=0 ;
        //input & save point
        scanf("%d%d",&r,&c) ;
        for(int i=1;i<=r;i++){
            scanf("%s",maze[i]+1) ;
            for(int j=1;j<=c;j++){
                char ch = maze[i][j] ;
                if(ch=='$') sr=i ,sc=j ; //start
                else if(ch=='&') er=i ,ec=j ; //end
                else if(isupper(ch))
                    port_r[ch-'A']=i ,port_c[ch-'A']=j ; //port
            }
        }
        solve(sr,sc) ;
        if(bfs[er][ec]==1) printf("Yes\n") ;
        else printf("No\n") ;
    }
}
void solve(int R,int C){
    //denote
    bfs[R][C]=1 ;
    //port
    char ch = maze[R][C] ;
    if(islower(ch)) solve(port_r[ch-'a'],port_c[ch-'a']) ;
    //spread
    else{
        for(int i=0;i<4;i++){
            int Y=R+y[i] ,X=C+x[i] ;
            if(Y<=r && Y>=1 && X<=c && X>=1){
                if(maze[Y][X]!='#' && bfs[Y][X]==0)
                    solve(Y,X) ;
            }
        }
    }
}


