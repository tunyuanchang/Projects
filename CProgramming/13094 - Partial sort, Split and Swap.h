#include <stdlib.h>
typedef struct _Node {
    int data;
    struct _Node *next;
} Node;

Node* Partial_sort(Node* head, int x){
    Node *newhead, *newlist = NULL ;  //< x
    Node *newhead1, *newlist1 = NULL ;  //>=x
    Node *cur = head ;
    while(cur!=NULL){
        if(cur->data<x){
            if(newlist==NULL) newhead = newlist = cur ;
            else newlist = newlist->next = cur ;
            cur = cur->next ;
        }
        else{
            if(newlist1==NULL) newhead1 = newlist1 = cur ;
            else newlist1 = newlist1->next = cur ;
            cur = cur->next ;
        }
    }
    if(newlist==NULL){  //all<x
        newlist1->next = NULL ;
        return newhead1 ;
    }
    if(newlist1==NULL){  //all>=x
        newlist->next = NULL ;
        return newhead ;
    }
    newlist->next = newhead1 ;
    newlist1->next = NULL ;
    return newhead ;
}

Node* Split_and_Swap(Node* head, int a, int b){
    Node *A = head, *B, *midleft, *midright, *end, *newend ;
    for(int i=0;head;i++,head = head->next){
        if(i==a) newend = head ;
        if(i==a+1) midleft = head ;
        if(i==b-1) midright = head ;
        if(i==b) B = head ;
        end = head ;
    }
    if(a==b-1){  //split into only two group
        end->next = A ;
        newend->next = NULL ;
        return B ;
    }
    end->next = midleft ;
    midright->next = A ;
    newend->next = NULL ;
    return B ;
}
