#include<stdio.h>
char C;
int D;
int main(){
    scanf("%c%d",&C,&D);
    int ans;
    if(C >= 'A' && C <= 'Z') ans = (C - 'A' - D + 26) % 26 + 'a';
    else ans = (C - 'a' - D + 26) % 26 + 'A';
    printf("%c\n",ans);
}
