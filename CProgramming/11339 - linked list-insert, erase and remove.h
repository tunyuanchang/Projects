#ifndef NODE
#define NODE
#include<stdio.h>
#include<stddef.h>
#include<stdlib.h>

typedef struct node{
	struct node *next;
	struct node *prev;
	unsigned short val;
}Node;

Node *create(unsigned short val){
    Node *temp = (Node*)calloc(1,sizeof(Node)) ;
    temp->val = val ;
    return temp ;
}

void do_I(Node **head,size_t pos,unsigned short val){
    Node *newnode, *cur = (*head) ;
    newnode = create(val) ;
    if((*head) == NULL || pos == 0){  //first position
        if((*head) != NULL) newnode->next = (*head), (*head)->prev = newnode ;
        (*head) = newnode ;
    }
    else{
        for(size_t i=1;i<pos;i++){
            if(cur->next == NULL) break ;
            cur = cur->next ;
        }
        //cur->next = node[pos]
        newnode->next = cur->next ;
        cur->next = newnode ;
        newnode->prev = cur ;
        if(newnode->next != NULL) newnode->next->prev = newnode ;
    }
    return ;
}
void do_E(Node **head,size_t begin_pos,size_t end_pos){
    if((*head) == NULL) return ;
    Node *cur = (*head), *L = NULL, *temp ;
    if(begin_pos == end_pos) return ;
    for(size_t i=0;i < end_pos;i++){
        if(i == begin_pos) L = cur ;
        if(cur->next == NULL){
            if(L == NULL) return ;
            break ;
        }
        if(i < end_pos - 1) cur = cur->next ;
    }  //cur->next = R
    if((*head) == L){
        (*head) = cur->next ;
        if((*head) != NULL) (*head)->prev = NULL ;
    }
    else{
        L->prev->next = cur->next ;
        if(cur->next != NULL) cur->next->prev = L->prev ;
    }
    cur->next = NULL ;
    while(L != NULL){
        temp = L ;
        L = L->next ;
        free(temp) ;
    }
}
void do_P(Node  *head,size_t pos){
    if(head == NULL) return ;
    while(pos--){
        if(head->next == NULL) break ;
        head = head->next ;
    }
    printf("%d ",head->val) ;
}
void do_R(Node **head,unsigned short val){
    Node *temp, *cur = (*head) ;
    while(cur != NULL){
        if(cur->val == val){
            if(cur == (*head)){
                (*head) = cur->next ;
                if((*head) != NULL) (*head)->prev = NULL ;
            }
            else{
                cur->prev->next = cur->next ;
                if(cur->next != NULL) cur->next->prev = cur->prev ;
            }
            temp = cur ;
            cur = cur->next ;
            free(temp) ;
        }
        else cur = cur->next ;
    }
}
void do_S(Node  *head){
    while(head != NULL){
        printf("%d ",head->val) ;
        head = head->next ;
    }
}
#endif
