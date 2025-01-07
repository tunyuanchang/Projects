#include<stdio.h>
int a[2][5], ans[5] ;
int main(void){
    for(int i = 0 ; i < 2 ; i++)
        scanf("%d/%d %d:%d:%d",&a[i][0],&a[i][1],&a[i][2],&a[i][3],&a[i][4]) ; //input
    
    int M = 0, m = 1 ;
    for(int i = 0 ; i < 5 ; i++)
        if(a[0][i] > a[1][i]) break ;
        else if(a[0][i] < a[1][i]){
            M = 1, m = 0 ;
            break ;
        } //find big(M) & small(m)
    ans[4] = a[M][4] - a[m][4] ;
    if(ans[4] < 0) ans[4] += 60, a[M][3]-- ; //sec
    ans[3] = a[M][3] - a[m][3] ;
    if(ans[3] < 0) ans[3] += 60, a[M][2]-- ; //min
    ans[2] = a[M][2] - a[m][2] ;
    if(ans[2] < 0) ans[2] += 24, a[M][1]-- ; //hour
    ans[1] = a[M][1] - a[m][1] ;
    if(ans[1] < 0) ans[1] += 30, a[M][0]-- ; //day
    ans[0] = a[M][0] - a[m][0] ; //month

    printf("%d %d\n%02d:%02d:%02d\n",ans[0],ans[1],ans[2],ans[3],ans[4]) ;
}
