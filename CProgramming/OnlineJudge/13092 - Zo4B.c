#include<stdio.h>
int a ;
int board[6][6],ans[6][6] ;
int dx[4] = {0,0,1,-1},dy[4] = {1,-1,0,0} ;
void solve() ;
void copy() ;
void print() ;
void move(int ,int ,int ) ;
int main(){
    int y = 1, x = 1 ;
    while(scanf("%d",&a) != EOF){
        board[y][x] = a ;
        if(x==4 && y==4) solve(), y = x = 1 ;
        else if(x==4) x = 1, y++ ;
        else x++ ;
    }
}
void solve(){
    copy() ;
    for(int x=1;x<=4;x++) move(0,1,x) ;//up
    print() ;
    copy() ;
    for(int x=1;x<=4;x++) move(1,4,x) ;//down
    print() ;
    copy() ;
    for(int y=1;y<=4;y++) move(2,y,1) ;//right
    print() ;
    copy() ;
    for(int y=1;y<=4;y++) move(3,y,4) ;//left
    print() ;
}
void move(int t,int y,int x){
    for(int i=0;i<4;i++){
        if(ans[y+i*dy[t]][x+i*dx[t]]==0){  //align
            for(int j=i+1;j<4;j++){
                if(ans[y+j*dy[t]][x+j*dx[t]]){
                    ans[y+i*dy[t]][x+i*dx[t]] = ans[y+j*dy[t]][x+j*dx[t]] ;
                    ans[y+j*dy[t]][x+j*dx[t]] = 0 ;
                    i-- ;
                    break ;
                }
            }
        }
        else{
            for(int j=i+1;j<4;j++){
                if(ans[y+i*dy[t]][x+i*dx[t]]==ans[y+j*dy[t]][x+j*dx[t]]){
                    ans[y+i*dy[t]][x+i*dx[t]] *= 2 ;
                    ans[y+j*dy[t]][x+j*dx[t]] = 0 ;
                    break ;
                }
                else if(ans[y+j*dy[t]][x+j*dx[t]]) break ;
            }
        }
    }
}
void print(){
    int invalid = 1 ;
    for(int r=1;r<=4;r++){
        for(int c=1;c<=4;c++){
            if(ans[r][c]!=board[r][c]){
                invalid = 0 ;
                r = c = 5 ;
            }
        }
    }
    if(invalid) printf("Invalid\n") ;
    else{
        for(int r=1;r<=4;r++){
            for(int c=1;c<=4;c++){
                printf("%d",ans[r][c]) ;
                c==4 ? printf("\n") : printf(" ") ;
            }
        }
    }
}
void copy(){
    for(int y=1;y<=4;y++) for(int x=1;x<=4;x++) ans[y][x] = board[y][x] ;  //copy
}
