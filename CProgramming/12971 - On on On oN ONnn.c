#include<stdio.h>
int n,m ; //n row m column
int a[25][25] ;
long long ans=1e8 ;
int x[5]={0,-1,0,1,0} ,y[5]={0,0,-1,0,1} ; //delta x & delta y
int check() ; //all light turn on
void change(int ,int ) ; //turn on/off light
void on(int ,int ,long long ) ;
int main(){
    scanf("%d%d",&n,&m) ;
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) scanf("%d",&a[i][j]) ;
    on(1,1,0) ;
    if(ans==1e8) printf("no solution\n") ;
    else printf("%d\n",ans) ;
}
int check(){
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if(a[i][j]==0) return 0 ;
    return 1 ;
}
void change(int Y,int X){
    for(int i=0;i<5;i++){
        if(a[Y+y[i]][X+x[i]]) a[Y+y[i]][X+x[i]]=0 ;
        else a[Y+y[i]][X+x[i]]=1 ;
    }
}
void on(int y,int x,long long t){
    if(y>n){
        if(check()){
            if(ans>t) ans=t ;
        }
        return ;
    }
    else if(t>ans) return ;
    else{
        for(int j=0;j<2;j++){
            if(j==0){ //not change
                if(x==m) on(y+1,1,t) ;
                else on(y,x+1,t) ;
            }
            else{ //change
                change(y,x) ;
                if(x==m) on(y+1,1,t+1) ;
                else on(y,x+1,t+1) ;
                change(y,x) ;
            }
        }
    }
}
