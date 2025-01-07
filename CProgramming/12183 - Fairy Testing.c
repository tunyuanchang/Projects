#include<stdio.h>
#include<stdlib.h>
typedef struct node{
    int value, type ;  //value - 1/0  type - &/|/0
    struct node *left, *right, *parent ;
}Node ;

Node *variable[100001]; //the pointers pointing to the tree nodes

Node *create(int type){
    Node *temp = (Node*)calloc(1,sizeof(Node)) ;
    temp->type = type ;
    return temp ;
}
Node *parse(){
    Node *root ;
    int index ;
    char input[5] ;
    scanf("%1s",input) ;
    if(input[0] == '['){  //variables
        scanf("%d",&index) ;
        root = variable[index] ;
        scanf("%1s",input) ;
    }
    else{  //op
        root = create(input[0]) ;
        root->left = parse() ;
        root->left->parent = root ;
        root->right = parse() ;
        root->right->parent = root ;
    }
    return root ;
}
void update(Node *root){
    if(root == NULL) return ;
    if(root->type == '&') root->value = root->left->value && root->right->value ;
    if(root->type == '|') root->value = root->left->value || root->right->value ;
    update(root->parent) ;
}
void freeTree(Node *root){
    if(root == NULL) return ;
    freeTree(root->left) ;
    freeTree(root->right) ;
    free(root) ;
}
int main(){
    int t, n, m, x ;
    scanf("%d",&t) ;
    while(t--){
        scanf("%d %d",&n,&m) ;
        for(int i = 1;i <= n; i++) variable[i] = create(0) ;  //type 0 - variables
        Node *root = parse() ;
        while(m--){
            scanf("%d",&x) ;
            (variable[x]->value)  ?(variable[x]->value = 0) :(variable[x]->value = 1) ;  //flip
            update(variable[x]->parent) ;
            printf("%d\n",root->value) ;
        }
        delete(root) ;
    }
}