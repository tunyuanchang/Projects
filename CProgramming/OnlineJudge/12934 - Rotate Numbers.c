#include<stdio.h>
#include<string.h>
#define maxn 101
char a[maxn] ;
int ans[maxn] ;
int main(void){
    scanf("%s",a) ;
    int k = strlen(a), meaning = 1 ;
    for(int i = k - 1, j = 0 ; i >= 0 ; i--, j++) ans[j] = a[i] - '0' ; //upside
    for(int i = 0 ; i < k ; i++){
        switch (ans[i]){
            case 1 :
                ans[i] = 1 ;
            break ;
            case 6 :
                ans[i] = 9 ;
            break ;
            case 8 :
                ans[i] = 8 ;
            break ;
            case 9 :
                ans[i] = 6 ;
            break ;
            case 0 :
                ans[i] = 0 ;
            break ;
            default :
                meaning = 0 ;
            break ;
        }
        if(!meaning) break ;
    }
    if(meaning){
        int sum = 0 ;
        for(int i = 0 ; i < k ; i++){
            sum += ans[i] ;
            if(sum){
                if (i == k-1) printf("%d\n",ans[i]) ;
                else printf("%d",ans[i]) ;
            }
        }
    }
    else printf("No\n") ;
}
