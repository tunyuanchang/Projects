#include<bits/stdc++.h>
using namespace std;

class Node{
public:
    Node(unsigned long val) : value(val), left(NULL), right(NULL), next(NULL){ }
    unsigned long value;
    Node *left, *right, *next;
};

class Tree{
public:
    Tree() : root(NULL){ }
    Node *root;
};

class Chain{
    public:
        Chain() : head(NULL), tail(NULL){ }
        Node *head, *tail;
};

class Queue{
    public:
        Queue() : n(0){
            queue = new Chain();
        }
        bool Isempty(){
            return n == 0;
        }
        void Push(Node *node){
            if(Isempty()) queue->head = queue->tail = node;
            else queue->tail = queue->tail->next = node;
            n++;
        }
        void Pop(){
            if(!Isempty()){
                Node *temp = queue->head;
                queue->head = temp->next;
                delete temp;
                temp = NULL;
                n--;
            }
        }
        Node* Front(){
            return queue->head;
        }
        Node* Rear(){
            return queue->tail;
        }
        Chain *queue;
        unsigned long n;
};

string expr;
unsigned long pos, val;
unsigned long L, R, sz;
int skewed;
Tree *tree;
Queue *q;

Node* build(){
    if(expr[pos++] == '('){
        if(expr[pos] == ')'){
            pos++;
            return NULL;
        }
    }

    val = 0;
    while(expr[pos] >= '0' && expr[pos] <= '9'){
        val = val * 10 + (expr[pos] - '0');
        pos++;
    }
    Node *newnode = new Node(val);
    newnode->left = build();
    newnode->right = build();

    if(newnode->left != NULL && newnode->right != NULL) skewed = 0;

    if(expr[pos++] == ')') return newnode;
    return NULL;
}

unsigned long M(Node *node){
    unsigned long ans = 0;
    q = new Queue();
    q->Push(node);
    q->Front()->value = 1;
    while(!q->Isempty()){
        L = q->Front()->value;
        R = q->Rear()->value;
        sz = q->n;
        ans = max(ans, R - L + 1);
        for(unsigned long i = 0; i < sz ; ++i){
            Node *cur = q->Front();
            if(cur->left != NULL){
                cur->left->value = 2 * cur->value - 1;
                q->Push(cur->left);
            }
            if(cur->right != NULL){
                cur->right->value = 2 * cur->value;
                q->Push(cur->right);
            }
            q->Pop();
        }
    }
    return ans;
}

int main(){
    while(cin >> expr){
        pos = 0;
        skewed = 1;
        tree = new Tree();
        tree->root = build();
        if(skewed) cout << 0 << endl;
        else cout << M(tree->root) << endl;
    }
}
