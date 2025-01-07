#include<stdio.h>
#define maxn 102
int A,B ;
char a[maxn],b[maxn] ;
int numa[maxn],numb[maxn] ;
int ans[maxn] = {0} ;
int main(void){
    scanf("%d %s %d %s",&A,a,&B,b) ;
    int k = (A >= B) ? A : B ;
    for(int i = A - 1, j = 0 ; i >= 0 ; i--, j++) numa[j] = a[i] - '0' ;
    for(int i = B - 1, j = 0 ; i >= 0 ; i--, j++) numb[j] = b[i] - '0' ;
    for(int i = 0 ; i < k ; i++){
        ans[i] += numa[i] + numb[i] ;
        if(ans[i] >= 10) ans[i] %= 10, ans[i+1]++ ;
    }
    if(ans[k]) k++ ;
    for(int n = k-1 ; n >= 0 ; n--) printf("%d",ans[n]) ;
}
