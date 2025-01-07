#include<stdio.h>
#define maxn 101
int A,B ;
char a[maxn],b[maxn] ;
int num[2][maxn] ; //num[0][k] big & num[1][k] small
int ans[maxn] ;
int main(void){
    scanf("%d %s %d %s",&A,a,&B,b) ; //input

    int p = 0, q = 1, inver = 0 ; //inverse True/False
    int k = A ; //k highest digit
    if (A < B) p = 1, q = 0, inver = 1, k = B ;
    else if (A == B){
        for(int i = 0 ; i < A ; ){
            if(a[i] < b[i]){
                p = 1, q = 0, inver = 1, k = B-i ;
                break ; 
            }
            else if(a[i] > b[i]){
                k = A-i ;
                break ; 
            }
            else k = A-i, i++ ;
    } //find big & small

    for(int i = A - 1, j = 0 ; i >= 0 ; i--, j++) num[p][j] = a[i]-'0' ;
    for(int i = B - 1, j = 0 ; i >= 0 ; i--, j++) num[q][j] = b[i]-'0' ; //upside

    for(int i = 0 ; i < k ; i++){  //calculate
        if(num[0][i] >= num[1][i]) ans[i] = num[0][i] - num[1][i] ;
        else{
            ans[i] = 10 + num[0][i] - num[1][i] ;
            num[0][i+1]-- ;
        }
    }
    if(inver) printf("-") ; //negative
    for(int n = k - 1 ; n >= 0 ; n--){
        printf("%d",ans[n]) ;
    }
}
