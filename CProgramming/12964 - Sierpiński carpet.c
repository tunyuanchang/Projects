#include<stdio.h>
#include<math.h>
int check(int i, int j, int l) ;
int main(void){
    int n,len ;
    scanf("%d",&n) ;
    len = pow(3,n) ;
    for(int y = 0 ; y < len ; y++){
        for(int x = 0 ; x < len ; x++){
            if(check(y, x, len / 3) == 1) printf("#") ;
            else printf(".") ;
        }
        printf("\n") ;
    }
}
int check(int i,int j,int l){
    if(l == 0) return 0 ;
    if(i >= l && i < l * 2 && j >= l && j < l * 2) return 1;
    else return check(i % l, j % l, l/3) ;
}
