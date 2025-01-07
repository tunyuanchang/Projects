#include<stdio.h>
#define maxn 501 //include 500
int n;
int a[maxn][maxn];
int main(){
    scanf ("%d",&n);
    int k = 1 , x = 1, y = 1; //k number x column y row
    int l = n; //l layer
    while (k <= 4 * n * n){ //(2n)^2
        while(x <= n + l) a[y][x++] = k++ ; //right
        x--, y++ ;
        while(y <= n + l) a[y++][x] = k++ ; //down
        y--, x-- ;
        while(x >= n - l + 1) a[y][x--] = k++ ; //left
        x++, y-- ;
        while(y >= n - l + 2) a[y--][x] = k++ ; //up
        y++, x++ ;
        l--;
    }
    for (int i = 1 ; i <= 2*n ; i++){
        for (int j = 1 ; j <= 2*n ; j++){
            if (j == 2*n) printf("%d\n",a[i][j]);  //next row
            else printf("%d ",a[i][j]);
        }
    }
}
