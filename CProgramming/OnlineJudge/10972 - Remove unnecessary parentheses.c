#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX 258

char expr[MAX] ;
int pos ;

typedef struct _Node {
    char data;
    struct _Node *left, *right;
} Node;

Node* create(char c) ;
Node* EXPR() ;
Node* FACTOR() ;
void printAns(Node *root);
void freeTree(Node *root);

Node* create(char c){
    Node *temp = (Node*)calloc(1,sizeof(Node)) ;
    temp->data = c ;
    return temp ;
}

Node* EXPR(){
    Node *node, *right, *left ;
    right = FACTOR() ;
    if(pos<0 || (expr[pos] != '&' && expr[pos] != '|')) return right ;  //ID
    else node = create(expr[pos]) ;  //factor
    pos-- ;
    left = EXPR() ;
    node->left =  left ; //expr
    node->right = right ;
    return node ;
}

Node* FACTOR(){
    Node *node ;
    if(expr[pos]==')'){  //(expr)
        pos-- ;
        node = EXPR() ;
    }
    else node = create(expr[pos]) ;  //ID
    pos-- ;
    return node ;
}

void printAns(Node *root){
    if(root != NULL){
        printAns(root->left) ;
        printf("%c",root->data) ;
        if(root->right != NULL && (root->right->data == '|' || root->right->data == '&')){  //right - factor
            printf("(") ;  
            printAns(root->right) ;
            printf(")") ;
        }
        else printAns(root->right) ;
    }
}

void freeTree(Node *root){
    if (root!=NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main(){
    scanf("%s",expr) ;
    pos = strlen(expr) - 1 ;
    Node *root = EXPR() ;
    printAns(root) ;
    freeTree(root) ;
}