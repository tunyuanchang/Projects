#include<stdio.h>
#include<string.h>
int m, l, r, k, len ;
char str[10005], temp[10005] ;
int main(){
    scanf("%s %d",str,&m) ;
    while(m--){
        scanf("%d%d%d",&l,&r,&k) ;
        l--, r-- ;
        len = r - l + 1 ;
        k %= len ;
        if(k==0) continue ;
        strncpy(temp,str+l,len) ;
        for(int i=0;i<len;i++) str[l + (i+k) % len] = temp[i] ;
    }
    printf("%s\n",str) ;
}
