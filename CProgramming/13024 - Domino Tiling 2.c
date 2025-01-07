#include<stdio.h>
int n,m,ans ;
int a[50][50] ;
int check() ;
void solve(int ,int) ;
int main(){
    scanf("%d%d",&n,&m) ;
    solve(0,0) ;
    printf("%d\n",ans) ;
}
int check(){
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            if(a[i][j]==0) return 0 ;
    return 1 ;
}
void solve(int i,int j){
    if(i==n){
        if(check()) ans++ ;
        return ;
    }
    else if(j==m)
        solve(i+1,0) ;
    else if(a[i][j])
        solve(i,j+1) ;
    else{
        if(!a[i][j+1] && j+1!=m){ //horizontal
            a[i][j]=a[i][j+1]=1 ;
            solve(i,j+1) ;
            a[i][j]=a[i][j+1]=0 ;
        }
        if(!a[i+1][j] && i+1!=n){ //vertical
            a[i][j]=a[i+1][j]=1 ;
            solve(i,j+1) ;
            a[i][j]=a[i+1][j]=0 ;
        }
    }
}
