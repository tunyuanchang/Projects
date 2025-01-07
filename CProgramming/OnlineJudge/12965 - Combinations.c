#include<stdio.h>
int n,m ;
int arr[30], data[30] ;
void combination(int i, int index) ;
int main(void){
    scanf("%d%d",&n,&m) ;
    for(int i = 0 ; i < n ; i++) scanf("%d",&arr[i]) ;
    combination(0,0) ;
}
void com(int i,int index){
    if(index == m){
        for(int x = 0 ; x < m ; x++)
            if(x == m-1) printf("%d\n", data[x]) ;
            else printf("%d ", data[x]) ;
        return ;
    }
    if(i >= n) return ;
    //choose
    data[index] = arr[i] ;
    combination(i + 1, index + 1) ;
    //not choose
    combination(i + 1, index) ;
}
