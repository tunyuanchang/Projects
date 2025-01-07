#include<stdio.h>
#include<stdlib.h>
#define swap(a,b) {a^=b;b^=a;a^=b;}
typedef struct _Node {
    int data;
    struct _Node *next;
} Node;

void sort_(Node* node){
    for(Node* i=node; i!=NULL; i=i->next)
        for(Node* j=i->next; j!=NULL; j=j->next)
            if(i->data > j->data) swap(i->data, j->data);
}

Node* Merge_lists(Node* a, Node* b){
    sort_(a) ;
    sort_(b) ;
    int choose ;
    Node *newlist = NULL , *cur = NULL ;
    while(a!=NULL || b!=NULL){
        if(cur==NULL) newlist = cur = (Node*)malloc(sizeof(Node)) ;  //first one
        else{
            //duplicated numbers
            while(a && a->data == cur->data) a = a->next ;
            while(b && b->data == cur->data) b = b->next ;
            if(a == NULL && b == NULL) break ;
            cur = cur->next = (Node*)malloc(sizeof(Node)) ;
        }
        if(a!=NULL && b!=NULL){
            if(a->data<=b->data) choose = 1 ;
            else choose = 2 ;
        }
        else if(a!=NULL) choose = 1 ;
        else if(b!=NULL) choose = 2 ;
        //choose
        if(choose==1){
            cur->data = a->data ;
            a = a->next ;
        }
        else{
            cur->data = b->data ;
            b = b->next ;
        }
    }
    return newlist ;
}
