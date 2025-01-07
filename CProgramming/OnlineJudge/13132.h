#ifndef FUNCTION_H
#define FUNCTION_H

typedef struct _Node{
    struct _Node *prev;
    struct _Node *next;
    int val;
    int tag;
}Node;

int n, k, q;
Node *head;

void push(int x);
void pop();
void programming_tanoshi();
void KuoYangTeTe();

#endif
