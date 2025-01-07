#include<stdio.h>
#include<stdlib.h>

int n,q,x ;
int arr[100005] ;

int cmp(const void* a,const void* b){
    int x= *(int*)a ;
    int y= *(int*)b ;
    if(x < y) return 1 ;
    if(x == y) return 0 ;
    return -1 ;
}

int main(){
    int index = 0 ;
    scanf("%d",&n) ;
    for(int i=0;i<n;i++) scanf("%d",&arr[i]) ;
    qsort(arr,n,sizeof(int),cmp) ;
    scanf("%d",&q) ;
    while(q--){
        scanf("%d",&x) ;
        for(int i=index;i<n;i++,index++)
            if(arr[i]<=x) break ;
        printf("%d\n",n-index) ;
    }
}
