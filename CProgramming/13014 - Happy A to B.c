#include<stdio.h>
#define swap(a,b) {a^=b;b^=a;a^=b;}
int k,valid ;
char a[5][5],b[5][5] ; //board
int x[4]={0,0,1,-1},y[4]={1,-1,0,0} ;
int check() ;
void solve(int ,int ,int) ;
int main(){
    int t,r,c ;
    scanf("%d",&t) ;
    while(t--){
        valid = 0 ; //reset
        scanf("%d",&k) ;
        for(int i=1;i<=3;i++) scanf("%s",a[i]+1) ;
        for(int i=1;i<=3;i++) scanf("%s",b[i]+1) ; //input
        for(int i=1;i<=3;i++){
            for(int j=1;j<=3;j++){
                if(a[i][j]=='x') r=i,c=j ; //start
            }
        }
        solve(r,c,0) ;
        if(valid) printf("Yes\n") ;
        else printf("No\n") ;
    }
}
int check(){
    for(int i=1;i<=3;i++)
        for(int j=1;j<=3;j++)
            if(a[i][j] != b[i][j]) return 0 ;
    return 1 ;
}
void solve(int R,int C,int count){
    if(count>k) return ;
    if(b[R][C]=='x') if(check()) valid=1 ;
    for(int n=0;n<4;n++){
        int Y=R+y[n],X=C+x[n] ;
        if(Y<=3 && Y>=1
           && X<=3 && X>=1){ //not over bound
            swap(a[R][C],a[Y][X]) ;
            solve(Y,X,count+1) ;
            swap(a[R][C],a[Y][X]) ;
        }
    }
}

