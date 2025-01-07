#ifndef FUNCTION_H
#define FUNCTION_H

#include<stdio.h>
#include<stdlib.h>

#define MAXEXPR 256
#define NUMSYM 6

char expr[MAXEXPR];  // string to store the input expression.
int pos;             // current position of parsing, from end to start

typedef enum {ID_A, ID_B, ID_C, ID_D, OP_AND, OP_OR}TokenSet;
char sym[NUMSYM];

typedef struct _Node{
    TokenSet data;
    struct _Node *left, *right;
}BTNode;

BTNode* makeNode(char c);
BTNode* EXPR();
BTNode* FACTOR();

BTNode* EXPR(){
    BTNode *node, *right, *left ;
    right = FACTOR() ;
    if(pos<0 || (expr[pos] != '&' && expr[pos] != '|')) return right ;  //finish / ID
    else node = makeNode(expr[pos]) ;  //factor
    pos-- ;
    left = EXPR() ;  //expr
    node->left = left ;
    node->right = right ;
    return node ;
}
BTNode* FACTOR(){
    BTNode *node ;
    if(expr[pos]==')'){  //(expr)
        pos-- ;
        node = EXPR() ;
    }
    else node = makeNode(expr[pos]) ;  //ID
    pos-- ;
    return node ;
}
BTNode* makeNode(char c){
    BTNode *newnode = (BTNode*)calloc(1,sizeof(BTNode)) ;
    switch (c){
        case 'A' :
            newnode->data = ID_A ;
            break ;
        case 'B' :
            newnode->data = ID_B ;
            break ;
        case 'C' :
            newnode->data = ID_C ;
            break ;
        case 'D' :
            newnode->data = ID_D ;
            break ;
        case '&' :
            newnode->data = OP_AND ;
            break ;
        case '|' :
            newnode->data = OP_OR ;
            break ;
    }
    return newnode ;
}

void freeTree(BTNode *root);
void printPrefix(BTNode *root);

#endif