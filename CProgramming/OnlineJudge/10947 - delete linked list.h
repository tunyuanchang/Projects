#include <stdlib.h>
#include <stdio.h>

typedef struct _Node {
    int data;
    struct _Node *next;
} Node;

void deleteNode(Node** head, int data){
    if(data == 1){
        (*head) = (*head)->next ;
        return ;
    }
    data-- ;
    Node *cur = (*head), *pre = NULL ;
    while(data-- && cur != NULL){
        pre = cur ;
        cur = cur->next ;
    }
    if(cur) pre->next = cur->next ;
    free(cur) ;
}
Node* createList(){
    int val ;
    Node *newnode, *temp, *cur ;
    newnode = (Node*)malloc(sizeof(Node)) ;
    scanf("%d",&newnode->data) ;
    newnode->next = NULL ;
    cur = newnode ;
    while(scanf("%d",&val) && val != -1){
        temp = (Node*)malloc(sizeof(Node)) ;
        temp->data = val ;
        cur = cur->next = temp ;
    }
    cur->next = NULL ;
    return newnode ;
}
