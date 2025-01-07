#include <stdio.h>
int n,m,q,r,ans ;
int place[10],queen[10] ;
int valid(int row,int col){
    for(int i=0;i<row;i++){
        if(queen[i] || queen[row]){
            if(place[i]==col || place[i]==col+row-i || place[i]==col-row+i) return 0 ;
        }
        if(place[i]==col) return 0 ;
    }
    return 1 ;
}
void solve(int row){
    if(row == n+m){
        ans++ ;
        return ;
    }
    for(int i=0;i<n+m;i++){
        place[row] = i ;
        if(q < n){
            queen[row] = 1 ;
            q++ ;
            if(valid(row,i)) solve(row+1) ;
            queen[row] = 0 ;
            q-- ;
            if(r < m){
                r++ ;
                if(valid(row,i)) solve(row+1) ;
                r-- ;
            }
        }
        else{
            if(r < m){
                r++ ;
                if(valid(row,i)) solve(row+1) ;
                r-- ;
            }
        }
    }
}
int main(){
    while(scanf("%d%d",&n,&m) != EOF){
        ans = 0, q = 0, r = 0 ;
        solve(0) ;
        printf("%d\n",ans) ;
    }
}
