#include <stdio.h>
#define maxn 1001
int n,m ;
char s[maxn] ;
int main(void){
    scanf("%d%s%d",&n,s,&m) ;
    for(int t = 0 ; t < m ; t++){
        unsigned long long p = 0, q = 0 ;
        int a, b, sz ;
        scanf("%d%d%d",&a,&b,&sz) ;
        for(int A = a, B = b ; A < a+sz, B < b+sz ; A++, B++){
            p *=10 ;
            p += s[A] - '0' ;
            q *= 10 ;
            q += s[B] - '0' ; //take out number and calculate
            s[A] = s[B] = '@' ; //denote number
        }
        printf("%llu\n",p * q) ;

        int j = 0 ;
        for(int i = 0 ; i < n ; i++){
            if(s[i] != '@') s[j++] = s[i] ; //remove number
        }
        n = j ; //shorten the string
    }
}
