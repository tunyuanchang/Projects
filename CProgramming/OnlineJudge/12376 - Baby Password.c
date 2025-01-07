#include<stdio.h>
char C ;
int D ;
int main(){
    scanf("%c%d",&C,&D);
    printf("%c\n",(C - 'A' - D + 26) % 26 + 'A');
}
