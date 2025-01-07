#include<stdio.h>
int n ; //n row*column
int s[15][15] ;
int a[15] ; //a[i]=n -> a star is on (i,n)
long long ans=-1e10 ;
void max() ;
void star(int row) ;
int valid(int row,int col) ;
int main(void){
    scanf("%d",&n) ;
    for(int i=0;i<n;i++) for(int j=0;j<n;j++) scanf("%d",&s[i][j]) ;
    star(0) ;
    if(ans==-1e10) printf("no solution\n") ;
    else printf("%lld\n",ans);
}
void star(int row){
    if(row==n) {
        max() ;
        return ;
    }
    else{
        for(int i=0;i<n;i++){
            if(valid(row,i)){
                a[row]=i ;
                star(row+1) ;
            }
        }
    }
}
int valid(int row, int col){
    for (int i=0; i<=row-1; i++){
        if(a[i]==col || a[i]==(col-row+i) || a[i]==(col+row-i) )
            return 0 ;
    }
    return 1 ;
}
void max(){
    long long max=0 ;
    for(int i=0;i<n;i++){
        max +=s[i][a[i]] ;
    }
    if(ans<max) ans=max ;
}
