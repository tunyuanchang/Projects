#include<stdio.h>
#include<stdlib.h>

typedef struct Block{
    long long data ;
    struct Block *next, *prev ;
}block ;

int n,q,t,k ;
block *head, *cur, *temp, *mid ;
long long arr[100005] ;
int cmp(const void* a,const void* b){
    long long x = *(long long*)a,y = *(long long*)b ;
    if(x > y) return 1 ;
    if(x == y) return 0 ;
    if(x < y) return -1 ;
}
block* bulid(long long val){
    block *newblock = (block*)malloc(sizeof(block)) ;
    newblock->data = val ;
    return newblock ;
}
int main(){
    scanf("%d",&n) ;
    for(int i=1;i<=n;i++) scanf("%lld",&arr[i]) ;
    qsort(arr+1,n,sizeof(long long),cmp) ;
    head = cur = bulid(-1) ;
    for(int i=1;i<=n;i++){
        cur->next = bulid(arr[i]) ;
        cur->next->prev = cur ;
        cur = cur->next ;
        if(i==(n+1)/2) mid = cur ;
    }
    cur->next = bulid(-1) ;
    int index2 = 0 ;  //time of 2
    scanf("%d",&q) ;
    while(q--){
        scanf("%d",&t) ;
        if(t==1){
            mid = mid->prev ;
            mid->next = mid->next->next ;
            mid->next->prev = mid ;
            n-- ;
            if(n%2) mid = mid->next ;
        }
        else if(t==2){
            scanf("%d",&k) ;
            block *K = head->next ;
            long long ans = 0 ;
            if(index2<60){
                for(int i=1;i<k;i++) K = K->next ;
                ans = K->data ;
            }
            printf("%lld\n",ans>>index2) ;
            index2 ++ ;
        }
    }
}
