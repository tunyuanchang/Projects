#ifndef FUNCTION_H
#define FUNCTION_H

#include<stdio.h>
#include<stdlib.h>

typedef struct _Node{
    struct _Node *prev;
    struct _Node *next;
    int val;
    int tag;
}Node;

int n, k, q;
int count, MID, TAG ;
Node *head, *tail = NULL, *mid = NULL ;

Node *create(int val){
    Node *temp = (Node*)calloc(1,sizeof(Node)) ;
    temp->val = val ;
    temp->tag = TAG ;
    return temp ;
}

void push(int x){
    Node *temp = create(x) ;
    if(count == 0) tail = NULL ;
    if(tail == NULL) head = tail = temp ;  //first
    else{
        temp->prev = tail ;
        tail = tail->next = temp ;
    }
    count++ ;
}

void pop(){
    if(count == 0) return ;
    int m = (count+1)/2 ;
    if(mid == NULL){
        mid = head ;
        for(int i=1;i<m;i++) mid = mid->next ;
    }
    else{
        for(int i=MID;i<m;i++) mid = mid->next ;
    }
    Node *temp = mid ;
    if(count % 2) MID = m-1, mid = mid->prev ;
    else MID = m, mid = mid->next ;
    if(temp->prev != NULL) temp->prev->next = temp->next ;
    if(temp->next != NULL) temp->next->prev = temp->prev ;
    free(temp) ;
    count-- ;
}

void programming_tanoshi(){
    TAG++ ;
}
void KuoYangTeTe(){
    Node *cur = head ;
    while(cur != NULL){
        if(cur->tag < TAG) cur->val %= k ;
        cur = cur->next ;
    }
}

#endif