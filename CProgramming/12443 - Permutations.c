#include<stdio.h>
int arr[15] ;
void swap(int *i,int *j) ;
void permutation(int a, int b) ; //i start j end
int main(void){
    int n ;
    scanf("%d",&n) ;
    for(int i = 1 ; i <= n ; i++) arr[i] = i ;
    permutation(1, n) ;
}
void swap(int *i, int *j){
    int temp ;
    temp = *i ;
    *i = *j ;
    *j = temp ;
}
void permutation(int a, int b){
    if(a == b){
        for(int i = 1 ; i <= j ; i++) printf("%d ",arr[i]) ;
        printf("\n") ;
        return ;
    }
    for(int i = a ; i <= b ; i++){
        swap(&arr[a], &arr[i]) ; //change first number
        //arr[a+1]~arr[i] sort
        for(int j = i ; j > a + 1 ; j--) swap(&arr[j], &arr[j-1]);
        permutation(a+1, b);
        //reverse sort
        for(int j = a + 1 ; j < i ; j++) swap(&arr[j], &arr[j+1]);
        swap(&arr[a], &arr[i]) ; //reset
    }
}
