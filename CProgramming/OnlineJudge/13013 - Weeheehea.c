#include<stdio.h>
int ans = 0 ;
char s[15] ;
int record[10][512] ; //record[x position][number]
int main(){
    int n,x ;
    scanf("%d",&n) ;
    for(int i=0;i<n;i++){
        scanf("%s",s) ;
        int num = 0 ;
        //x position
        for(int j=0;j<10;j++)
            if(s[j]=='x') x=j ;
        //number
        for(int j=0;j<10;j++){
            if(j==x) continue ;
            num *=2 ;
            num += (s[j]-'0');
        }
        record[x][num] ++ ;
    }
    for(int i=0;i<10;i++)
        for(int j=0;j<512;j++)
            if(record[i][j]) ans++ ;
    printf("%d\n",ans) ;
}
