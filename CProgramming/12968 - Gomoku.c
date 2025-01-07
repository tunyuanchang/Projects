#include<stdio.h>
char s[20][20] ;
void solve(int n){
    int i[5] = {1 , 0 , 1 , 1}, j[5] = {0 , 1 , 1 , -1} ; //i delta y  /j delta x
    for(int y = 0 ; y < n ; y++)
        for(int x = 0 ; x < n ; x++)
            if(s[y][x] != '.') {
                for(int t = 0 ; t < 4 ; t++){
                    int cnt = 0 ;
                    for(int k = 0 ; k < 5 ; k++) {
                        int Y = y + i[t] * k, X = x + j[t] * k ;
                        if(X < 0 || X >= n || Y < 0 || Y >= n)	break ;
                        if(s[Y][X] == s[y][x]) cnt++ ;
                    }
                    if(cnt == 5) {
                        if(s[y][x] == 'b') printf("black\n") ;
                        else printf("white\n") ;
                        return ;
                    }
                }
            }
    printf("none\n");
}
int main() {
    int q ;
    scanf("%d",&q) ;
    while(q--) {
        for(int i = 0 ; i < 15 ; i++) scanf("%s",s[i]) ;
        solve(15) ;
    }
}
