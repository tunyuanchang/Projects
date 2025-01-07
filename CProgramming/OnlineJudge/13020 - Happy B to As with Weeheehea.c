#include<stdio.h>
#include<math.h>
#define swap(a,b) {a^=b;b^=a;a^=b;}
#define pos(x,y) (3*(x-1)+(y-1))
int n,k,count ;
int start[2] ;
char a[100005][5][5] ;
int record[9][512] ; //record[savex][savenum]
int dx[4]={0,0,1,-1},dy[4]={1,-1,0,0} ;
int savex(int i){
    for(int y=1;y<=3;y++) for(int x=1;x<=3;x++)
        if(a[i][y][x]=='x') return pos(x,y) ;
}
int savenum(int i){
    int sum=0 ;
    for(int y=1;y<=3;y++) for(int x=1;x<=3;x++)
        if(a[i][y][x]=='1') sum +=pow(2,pos(x,y)) ;
    return sum ;
}
void board(int r,int c,int t){
    record[savex(n)][savenum(n)] = 1 ;
    if(t==k) return ;
    for(int i=0;i<4;i++){
        int R=r+dy[i],C=c+dx[i] ;
        if(C>=1 && C<=3 && R>=1 && R<=3){
            swap(a[n][r][c],a[n][R][C]) ;
            board(R,C,t+1) ;
            swap(a[n][r][c],a[n][R][C]) ;
        }
    }
}
int main(){
    scanf("%d%d",&n,&k) ;
    for(int i=0;i<=n;i++) for(int j=1;j<=3;j++) scanf("%s",a[i][j]+1) ;
    for(int i=1;i<=3;i++) for(int j=1;j<=3;j++)
        if(a[n][i][j]=='x') start[0]=i ,start[1]=j ;
    board(start[0],start[1],0) ;
    for(int i=0;i<n;i++) if(record[savex(i)][savenum(i)]) count++ ;
    printf("%d\n",count) ;
}
