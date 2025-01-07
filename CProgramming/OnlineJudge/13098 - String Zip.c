#include<stdio.h>
#include<string.h>
#include<ctype.h>

int index ;
double len,LEN ;
double rate ;
int arr[1005] ;
char str[1005] ;
void solve() ;
int main(){
    scanf("%s",str) ;
    LEN = strlen(str) ;
    for(int i=0;i<LEN;i++){
        if(i==0) arr[i] = 1,index = i ;
        else {
            if(str[i]==str[i-1]) arr[index]++ ;
            else arr[i] = 1,index = i ;
        }
    }
    solve() ;
    rate = len / LEN ;
    if(rate<1.0) printf("Compress rate: %.3f\n",rate) ;
    else printf("The string can't zip\n") ;
}
void solve(){
    for(int i=0;i<LEN;i++){
        if(arr[i]){
            if(isdigit(str[i])){
                if(arr[i] > 1){
                    printf("%d'%c'",arr[i],str[i]) ;
                    len = len + 4 + (arr[i] / 10) + (arr[i] / 100) + (arr[i] / 1000) ;
                }
                else{
                    printf("'%c'",str[i]) ;
                    len += 3 ;
                }
            }
            else{
                if(arr[i] >= 3){
                    printf("%d%c",arr[i],str[i]) ;
                    len = len + 2 + (arr[i] / 10) + (arr[i] / 100) + (arr[i] / 1000) ;
                }
                else{
                    for(int t=0;t<arr[i];t++) printf("%c",str[i]) ;
                    len += arr[i] ;
                }
            }
        }
    }
    printf("\n") ;
}
