#ifndef FUNCTION_H
#define FUNCTION_H

#include<stdlib.h>
#include<math.h>

int all_operation[300009];

typedef struct _Node{
    struct _Node *prev;
    struct _Node *next;
    int val;
    int tag; // use this variable to store which operation will be performed on this element 
}Node;

Node *head, *tail, *mid = NULL;
int sz, M, TAG = 0;

Node* create(int x){
    Node *temp = (Node*)calloc(1,sizeof(Node));
    temp->val = x;
    temp->tag = TAG;
    return temp;
}

void push(int x){
    Node *temp = create(x) ;
    if(sz == 0) tail = NULL;
    if(tail == NULL || head == NULL) head = tail = temp;
    else{
        temp->prev = tail;
        tail = tail->next = temp;
    }
    sz++;
}

void pop(){
    if(sz == 0) return;
    int m = (sz + 1) / 2;
    if(mid == NULL){
        mid = head;
        for(int i = 1 ; i < m ; i++) mid = mid->next;
    }
    else for(int i = M ; i < m ; i++) mid = mid->next;
    Node *temp = mid;
    if(sz % 2){
        M = m - 1;
        if(sz == 1) head = mid = NULL;
        else mid = mid->prev;
    }
    else{
        M = m;
        if(sz == 2) head = mid = head->next, head->prev = NULL;
        else mid = mid->next;
    }
    if(temp->prev != NULL) temp->prev->next = temp->next;
    if(temp->next != NULL) temp->next->prev = temp->prev;
    free(temp);
    sz--;
}

void programming_tanoshi(int k){
    if(sz == 0 || k == 1) return;
    TAG++;
    all_operation[TAG] = k;
}

void IP2_sugoi(){
    if(sz == 0) return;
    TAG++;
    all_operation[TAG] = 10;
}

void KuoYangTeTe(){ //You can either use this function or not depending on how you solve this problem
    if(sz == 0 || TAG == 0) return;
    Node *cur, *newhead = head;
    int count;
    for(int i = 0 ; i <= TAG ; i++){
        cur = newhead ;
        count = 1;
        while(cur != NULL){
            if(cur->val == 1){
                if(count) newhead = cur;
                cur = cur->next ;
                continue;
            }
            count = 0;
            if(cur->tag < i){
                if(all_operation[i] == 10)  //sugoi
                    cur->val = (int)floor(sqrt((double)cur->val));
                else if(all_operation[i] > 1 && all_operation[i] < 10)  //tanoshi
                    cur->val = (int)ceil((double)cur->val / all_operation[i]);
                cur = cur->next;
            }
            else break;
        }
    }
}

#endif