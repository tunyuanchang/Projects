#include<bits/stdc++.h>
using namespace std;

class Node{
public:
    Node(int val) : value(val), line(0), cnt(0), pt(0), left(NULL), right(NULL){ }
    int value, line, cnt, pt, del;
    Node *left, *right;
};

class Tree{
public:
    Tree() : root(NULL){ }
    Node *root;
};

string expr, instruction;
int pos, val, sign;
int tower, num;
Tree *tree;
long long one = 1;

void preorder(Node *node){
    if(node == NULL) return;
    cout << node->value << ' ';
    preorder(node->left);
    preorder(node->right);
}
void inorder(Node *node){
    if(node == NULL) return;
    inorder(node->left);
    cout << node->value << ' ';
    inorder(node->right);
}
void postorder(Node *node){
    if(node == NULL) return;
    postorder(node->left);
    postorder(node->right);
    cout << node->value << ' ';
}

void Traverse(Node *node){
    preorder(node);
    cout << endl;
    inorder(node);
    cout << endl;
    postorder(node);
    cout << endl;
}

long long WeightSum(Node *node){
    if(node == NULL) return 0;
    return (long long)node->value + WeightSum(node->left) + WeightSum(node->right);
}

long long MaximumPathSum(Node *node){
    if(node == NULL) return 0;

    if(node->left == NULL && node->right == NULL) return node->value;
    else if(node->left == NULL) return node->value + MaximumPathSum(node->right);
    else if(node->right == NULL) return node->value + MaximumPathSum(node->left);
    else return node->value + max(MaximumPathSum(node->left), MaximumPathSum(node->right)); 
}

void BinaryTower(Node *node){
    if(node == NULL) return;
    
    BinaryTower(node->left);
    BinaryTower(node->right);

    if(node->left == NULL && node->right == NULL) node->pt = 0;
    else if(node->left == NULL){
        if(node->right->pt == 0) tower++, node->pt = 2;
        else if(node->right->pt == 2) node->pt = 1;
        else node->pt = 0;
    }else if(node->right == NULL){
        if(node->left->pt == 0) tower++, node->pt = 2;
        else if(node->left->pt == 2) node->pt = 1;
        else node->pt = 0;
    }else{
        if(node->left->pt == 0 || node->right->pt == 0)
            tower++, node->pt = 2;
        else if(node->left->pt == 2 || node->right->pt == 2)
            node->pt = 1;
        else node->pt = 0;
    }
}

void KingdomUnitedPath(Node *node){
    if(node == NULL) return;

    KingdomUnitedPath(node->left);
    KingdomUnitedPath(node->right);

    if(node->left == NULL && node->right == NULL) node->line = 0;
    else if(node->left == NULL)
        node->line = (node->value == node->right->value) ?1 + node->right->line :0;
    else if(node->right == NULL)
        node->line = (node->value == node->left->value) ?1 + node->left->line :0;
    else{
        if(node->value == node->left->value && node->value == node->right->value){
            node->cnt = 2 + node->left->line + node->right->line;
            node->line = 1 + max(node->left->line, node->right->line);
        }
        else if(node->value == node->left->value)
            node->line = 1 + node->left->line;
        else if(node->value == node->right->value)
            node->line = 1 + node->right->line;
        else node->line = 0;
    }
	int choose = (node->cnt) ?node->cnt :node->line;
    num = max(num, choose);
}

bool Foldable(Node *node1, Node *node2){
    if(node1 == NULL && node2 == NULL) return true;
    if(node1 == NULL || node2 == NULL) return false;
    return Foldable(node1->left, node2->right) & Foldable(node1->right, node2->left);
}

Node* build(){
    if(expr[pos++] == '('){
        if(expr[pos] == ')'){
            pos++;
            return NULL;
        }
    }

    val = 0;
    if(expr[pos] == '-') sign = -1, pos++;
    else sign = 1;
    while(expr[pos] >= '0' && expr[pos] <= '9'){
        val = val * 10 + (expr[pos] - '0');
        pos++;
    }
    Node *newnode = new Node(val * sign);
    newnode->left = build();
    newnode->right = build();

    if(expr[pos++] == ')') return newnode;
    return NULL;
}

Node* DeleteLeaf(Node *node){
    if(node == NULL) return node;

    if(node->left == NULL && node->right == NULL){
        delete node;
        return NULL;
    }

    node->left = DeleteLeaf(node->left);
    node->right = DeleteLeaf(node->right);

    return node;
}

Node* Invert(Node *node){
    if(node == NULL) return node;
    
    Node *L = node->left, *R = node->right;
    node->left = Invert(R);
    node->right = Invert(L);
    return node;
}

int main(){
    while(cin >> expr){
        tree = new Tree(), pos = 0;
        tree->root = build();
        while(cin >> instruction){
            if(instruction == "Traverse"){
                Traverse(tree->root);
            }else if(instruction == "WeightSum"){
                cout << WeightSum(tree->root) << endl;
            }else if(instruction == "MaximumPathSum"){
                cout << MaximumPathSum(tree->root) << endl;
            }else if(instruction == "BinaryTower"){
                tower = 0;
                BinaryTower(tree->root);
                if(tree->root != NULL) if(tree->root->pt == 0) tower++;
                cout << tower << endl;
            }else if(instruction == "Foldable"){
                if(Foldable(tree->root, tree->root)) cout << "Yes" << endl;
                else cout << "No" << endl;
            }else if(instruction == "DeleteLeaf"){
                tree->root = DeleteLeaf(tree->root);
            }else if(instruction == "Invert"){
                tree->root = Invert(tree->root);
            }else if(instruction == "KingdomUnitedPath"){
                num = 0;
                KingdomUnitedPath(tree->root);
                cout << num << endl;
            }
            else if(instruction == "End"){
                cout << endl;
                break;
            }
        }
    }
}
