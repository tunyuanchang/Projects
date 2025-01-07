#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    int data ;
    struct node *left, *right ;
}Node ;

int height = 0, sum[10000] = {0}, num[10000] = {0} ;
//Max_height, sum of level[i], number of level[i]

Node* create(int data){
    Node *temp = (Node*)calloc(1,sizeof(Node)) ;
    temp->data = data ;
    return temp ;
}

void add(Node** root, int data, int level){
    if((*root) == NULL){
        if(height < level) height = level ;
        sum[level] += data ;
        num[level] ++ ;
        (*root) = create(data) ;
        return ;
    }
    else{
        if(data < (*root)->data) return add(&(*root)->left,data,level+1) ;
        else if(data > (*root)->data) return add(&(*root)->right,data,level+1) ;
    }
}

void print_inorder(Node *root){
    if(root == NULL) return ;
    print_inorder(root->left) ;
    printf("%d ",root->data) ;
    print_inorder(root->right) ;
}
int main(){
    int n, data, m, input ;
    char op[20] ;
    Node *root = NULL ;
    scanf("%d",&n) ;
    while(n--){
        scanf("%d",&data) ;
        add(&root,data,1) ;
    }
    scanf("%d",&m) ;
    while(m--){
        scanf("%s",op) ;
        if(op[0] == 'P'){  //P
            if(root == NULL) printf("NULL") ;
            else print_inorder(root) ;
            printf("\n") ;
        }
        else if(op[0] == 'G'){  //GetMax
            printf("%d\n",height) ;
        }
        else if(op[0] == 'S'){  //SumLevel
            scanf("%d",&input) ;
            if(input <= 0 || input > height) printf("0\n") ;
            else printf("%d\n",sum[input]) ;
        }
        else if(op[0] == 'A'){  //AverLevel
            scanf("%d",&input) ;
            if(input <= 0 || input > height) printf("0\n") ;
            else printf("%.3f\n",(float)sum[input]/num[input]) ;
        }
    }
}