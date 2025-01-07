#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int num ;
    struct Node* next ; //link next
}node ;

node* create(int num){
    node* NODE = (node*)malloc(sizeof(node)) ;
    NODE->num = num ;
    NODE->next = NULL ;
    return NODE ;
}

int cmp(const void* a, const void* b){
    int x = *(int* )a ;
    int y = *(int* )b ;
    if(x > y) return 1 ;
    if(x == y) return 0 ;
    return -1 ;
}

int n,q,t,x ; //t type
int arr[100005] ;
node *start, *end, *cur, *X, *Y, *temp ;

int main(){
    scanf("%d",&n) ;
    for(int i=0;i<n;i++) scanf("%d",&arr[i]) ;
    qsort(arr,n,sizeof(int),cmp) ; //sort
    //set
    X = Y = cur = start = create(0) ;
    for(int i=0;i<n;i++) cur = cur->next = create(arr[i]) ;
    end = cur = cur->next = create(0) ;
    scanf("%d",&q) ;
    while(q--){
        scanf("%d%d",&t,&x) ;
        switch (t) {
            case 1 :
                while(X->next != end && X->next->num < x) X = X->next ;
                if(X->next->num == x){
                    temp = X->next ;
                    X->next = X->next->next ;
                    free(temp) ;
                }
                break ;
            case 2 :
                while(Y->next != end && Y->next->num < x) Y = Y->next ;
                if(Y->next->num == x) printf("Yes\n") ;
                else printf("No\n") ;
                break ;
        }
    }
}
