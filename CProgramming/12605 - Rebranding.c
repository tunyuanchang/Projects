#include<stdio.h>
#include<string.h>
int n, m ;
int turn[26] ;
char name[200005], x, y ;
int main(){
    for(int i=0;i<26;i++) turn[i] = i ;
    scanf("%d %d %s",&n,&m,name) ;
    while(m--){
        scanf("%s %s",&x,&y) ;
        for(int i=0;i<26;i++){
            if(turn[i] == x-'a') turn[i] = y - 'a' ;
            else if(turn[i] == y-'a') turn[i] = x - 'a' ;
        }
    }
    for(int i=0;i<n;i++) name[i] = 'a' + turn[name[i]-'a'] ;
    puts(name) ;
}
