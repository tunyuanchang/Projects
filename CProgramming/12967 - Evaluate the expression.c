#include<stdio.h>
#include<string.h>
char s[10000] ;
int main(void){
    scanf("%s",s) ;
    int n = 1, t = 1, m = 1 ; //n number of interger / t - 1:+ | -1:- / m - 1:() | -1:()
    long long ans = 0 ;
    long long temp[105]={0} ;
    for(int i = 0; i <= strlen(s) ; i++) {
        if(s[i]=='(') continue ;
        else if(s[i]==')'){
            m = 1 ;
            continue ;
        }
        else if(s[i]=='+') t = 1, n++ ;
        else if(s[i]=='-') {
                if(s[i+1]=='(') m = -1, t = 1 ;
                else t = -1 ;
                n++ ;
        }
        else if(s[i] >= '0' && s[i] <= '9'){
            temp[n] *= 10 ;
            temp[n] += m * t * (s[i] - '0') ;
        }
    }
    for(int i = 1 ; i <= n + 1 ; i++) ans += temp[i] ;
    printf("%lld\n",ans) ;
}
