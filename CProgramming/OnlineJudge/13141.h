#ifndef FUNCTION_H
#define FUNCTION_H

int all_operation[300009];

typedef struct _Node{
    struct _Node *prev;
    struct _Node *next;
    int val;
    int tag; // use this variable to store which operation will be performed on this element 
}Node;

Node *head;
int sz;

void push(int x);
void pop();
void programming_tanoshi(int k);
void IP2_sugoi();
void KuoYangTeTe(); //You can either use this function or not depending on how you solve this problem

#endif
