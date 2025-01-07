#include <bits/stdc++.h>
using namespace std;

class Node{
    public:
        Node(unsigned long long r, unsigned long long c) : row(r), col(c), pre(NULL){ }
        unsigned long long row, col;
        Node *pre;
};

class Chain{
    public:
        Chain() : tail(NULL){ }
        Node *tail;
};

class Stack{
    public:
        Stack() : n(0){
            stack = new Chain();
        }
        bool Isempty(){
            return n == 0;
        }
        void Push(Node *p){
            if(Isempty()) stack->tail = p;
            else{
                p->pre = stack->tail;
                stack->tail = p;
            }
            n++;
        }
        void Pop(){
            stack->tail = stack->tail->pre;
            n--;
        }
        Node* Top(){
            return stack->tail;
        }
        Chain *stack;
        int n;
};

int main(){
    int t, q, invalid;
    unsigned long long n, m, ans;
    char c, expr[2005];

    Node *matrix[26], *a, *b, *newnode;
    Stack* stack;
    
    cin >> t;
    for(int i = 0 ; i < t ; i++){
        cin >> c >> n >> m;
        matrix[c - 'A'] = new Node(n, m);
    }
    
    cin >> q;
    for(int i = 0 ; i < q ; i++){
        stack = new Stack();
        ans = invalid = 0;
        cin >> expr;
        for(int i = 0 ; i < strlen(expr) ; i++){
            if(expr[i] == ')'){
                b = stack->Top();
                stack->Pop();
                a = stack->Top();
                stack->Pop();
                if(a->col != b->row) invalid = 1;
                else{
                    ans += a->row * a->col * b->col;
                    newnode = new Node(a->row, b->col);
                    stack->Push(newnode);
                }
            }
            else if(expr[i] == '(') continue;
            else stack->Push(matrix[expr[i] - 'A']);
            if(invalid) break;
        }
        if(invalid) cout << "error" << endl;
        else cout << ans << endl;
    }
}
