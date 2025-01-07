#include<stdio.h>
#define maxn 501
int n,m,q,x ;
char row[maxn][maxn] ;
int main(void){
    scanf("%d%d",&n,&m) ;
    for(int i = 1 ; i <= n ; i++){
        scanf("%s",row[i]+1) ; //input
    }
    scanf("%d",&q) ;
    while(q--){
        scanf("%d",&x) ;
        int type = 3 ;
        for(int i = 1 ; i <= n ; i++){
            if(row[i][x] == '\\') {
                if(x == m){
                    type = 2 ;
                    break ;
                }
                if(row[i][x+1] == '\\') x++ ;
                else{
                    type = 0 ;
                    break ;
                }
            }
            else if(row[i][x] == '/'){
                if(x == 1){
                    type = 1 ;
                    break ;
                }
                if(row[i][x-1] == '/') x--;
                else{
                    type = 0 ;
                    break ;
                }
            }
        }
        if(type == 0) printf("Stuck QQ\n");
        else if(type == 1) printf("Left!\n");
        else if(type == 2) printf("Right!\n");
        else printf("Position: %d\n",x);
    }
}
