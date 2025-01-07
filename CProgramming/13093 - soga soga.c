#include<stdio.h>
#include<stdlib.h>

typedef struct Block{
    int num ;
    struct Block *prev, *next ;
}block ;

block* build(int val){
    block* newblock = (block*)malloc(sizeof(block)) ;
    newblock->num = val ;
    return newblock ;
}

int n,a,q,t,dir ;
block *cur, *head, *mid ;

int main(){
    scanf("%d",&n) ;
    //set
    head = cur = build(-1) ;
    for(int i=1;i<=n;i++){
        scanf("%d",&a) ;
        cur->next = build(a) ;
        cur->next->prev = cur ;
        cur = cur->next ;
    }
    cur->next = build(-1) ;
    cur = mid = head->next ;
    for(int i=1;i<(n%2==0 ?n/2 :n/2+1);i++) mid = mid->next ;

    scanf("%d",&q) ;
    while(q--){
        scanf("%d",&t) ;
        if(t==1){
            scanf("%d",&dir) ;
            if(dir==-1) cur = cur->prev ;
            else cur = cur->next ;
        }
        else if(t==2) printf("%d\n",cur->num) ;
        else{
            block *temp = mid ;
            mid->prev->next = mid->next ;
            mid->next->prev = mid->prev ;
            if(cur==mid) cur = cur->next ;
            mid = n%2==0 ?mid->next :mid->prev ;
            free(temp) ;
            n-- ;
        }
    }
}
