#include<stdio.h>
int main(){
    int X,Y,Z;
    scanf("%d%d%d",&X,&Y,&Z);
    printf("%d %d %d\n",(X + Y + Z) / 2 - Y,(X + Y + Z) / 2 - Z,(X + Y + Z) / 2 - X);
    return 0;
}
