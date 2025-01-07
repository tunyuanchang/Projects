#include<stdio.h>
#include<stdlib.h>
#define swap(a,b) {a^=b;b^=a;a^=b;}

typedef struct _Node {
    int data;
    struct _Node *next;
} Node;

Node* createList(int *a, int size){
    Node *head, *cur, *newnode ;
    for(int i=0;i<size;i++){
        newnode = (Node*)malloc(sizeof(Node)) ;
        if(i==0) head = cur = newnode ;
        else cur = cur->next = newnode ;
        newnode->data = a[i];
    }
    cur->next = NULL ;
    return head ;
}
void push_front(Node** head, int val){
    Node* newnode = (Node*)malloc(sizeof(Node)) ;
    newnode->data = val ;
    newnode->next = (*head) ;
    (*head) = newnode ;
}
void deleteElementByIdx(Node** head, int idx){
    Node *cur = (*head), *temp ;
    if(idx == 0){
        temp = cur ;
        cur = cur->next ;
    }
    else{
        idx -- ;
        while(idx-- && cur->next != NULL) cur = cur->next ;
        if (cur->next == NULL) return ;  //can't find
        temp = cur->next ;
        cur->next = cur->next->next ;
    }
    free(temp) ;
}
Node* copyList(Node* head){
    Node *copylist = NULL, *cur = NULL ;
    while(head != NULL){
        Node *newnode = (Node*)malloc(sizeof(Node)) ;
        if(cur == NULL) copylist = cur = newnode ;
        else cur = cur->next = newnode ;
        newnode->data = head->data;
        head = head->next;
    }
    cur->next = NULL ;
    return copylist ;
}
void SwapElementByIdx(Node** head, int idx1, int idx2){
    if(idx1 > idx2) swap(idx1,idx2) ;
    Node *cur = (*head), *a, *b ;
    for(int i=0 ;cur!=NULL && i<=idx2;i++ ,cur=cur->next){
        if(i == idx1) a = cur ;
        else if(i == idx2) b = cur ;
    }
    if(a->data != b->data) swap(a->data,b->data) ;
}
void ReverseList(Node** head){
    Node *cur = (*head), *prev = NULL, *temp ;
    while(cur){
        temp = prev ;
        prev = cur ;
        cur = cur->next ;
        prev->next = temp ;
    }
    (*head) = prev ;
}
void ShiftListByK(Node** head, int k){
    Node *cur, *end, *temp ;
    int len = 0 ;
    for(Node *count=(*head);count;count=count->next){
        len++ ;
        end = count ;
    }
    k %= len ;
    if(k==0) return ;
    k = len - k ;
    cur = (*head) ;
    for(int i=0;i<k;i++){
        temp = cur ;
        cur = cur->next ;
    }
    temp->next = NULL ;  //new end
    end->next = (*head) ;  //end link head
    (*head) = cur ;  //new head
}
