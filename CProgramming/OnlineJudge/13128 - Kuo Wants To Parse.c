#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h> //for isdigit() 

typedef struct _Node {
    int value;
    char OP;
    struct _Node *left;
    struct _Node *right;
} Node;

char expr[120];
int pos;
Node *head;

Node* Factor();
Node* Expr();
void PrefixPrint(Node* node);

Node* CreateNode(){
    Node *newNode = (Node*) calloc(1,sizeof(Node));
    if(isdigit(expr[pos])){
        for(int i = pos - 1 ; i >= 0 && isdigit(expr[i]) ; i--) pos--;
        sscanf(expr+pos,"%d",&newNode->value);
    }
    else newNode->OP = expr[pos];
    return newNode;
}

Node* Factor(){
    Node *root;
    if(expr[pos] == ')'){
        pos--;
        root = Expr();
        pos--;
    }
    else root = CreateNode(expr[pos]);
    return root;
}
Node* Expr(){
    Node *right, *root;
    right = Factor();
    if(pos <= 0 || expr[pos-1] == '(') return right;
    pos--;
    root = CreateNode() ;
    root->right = right;
    pos--;
    root->left = Expr();
    return root;
}
void PrefixPrint(Node* node){
    if(node == NULL) return;
    if(node->value) printf("%d ",node->value);
    else printf("%c ",node->OP);
    PrefixPrint(node->left);
    PrefixPrint(node->right);
}
int main() {
    while((scanf("%s" , expr)) != EOF) {
        pos = strlen(expr) - 1;
        head = Expr();
        PrefixPrint(head);
        printf("\n");
        head = NULL; 
    }
    return 0;
}