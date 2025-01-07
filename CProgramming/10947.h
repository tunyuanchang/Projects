#include <stdlib.h>
#include <stdio.h>

typedef struct _Node {
    int data;
    struct _Node *next;
} Node;

Node* createList();
void deleteNode(Node ** nd, int data);
