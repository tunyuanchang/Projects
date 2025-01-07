#include<stdio.h>
#include<stdlib.h>
typedef struct _Node{
    char data ;
    struct _Node *left, *right ;
}Node ;
int pos = 0 ;
char expr[35] ;
Node* create(char c){
    Node *temp = (Node*)calloc(1,sizeof(Node)) ;
    temp->data = c ;
    return temp ;
}
Node* build(){
    Node *newnode = create(expr[pos]) ;
    if(expr[pos] == 0 || (expr[pos] != '&' && expr[pos] != '|')) return newnode ;
    pos++ ;
    newnode->left = build() ;
    pos++ ;
    newnode->right = build() ;
    return newnode ;
}
int solve(Node *root, int n){
    if(root->data == '&') return solve(root->left,n) && solve(root->right,n) ;
    else if(root->data == '|') return solve(root->left,n) || solve(root->right,n) ;
    else return 1 & (n>>(3-(root->data-'A'))) ;
}
int main(){
    scanf("%s",expr) ;
    Node *root = build() ;
    for(int i=0;i<16;i++){
        printf("%d %d %d %d ",(i>>3) & 1,(i>>2) & 1,(i>>1) & 1,i & 1) ;
        printf("%d\n",solve(root,i)) ;
    }
}