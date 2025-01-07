#include<bits/stdc++.h>
using namespace std;

class Node;
class Chain;

class Node{
    public:
        Node(int value) : index(value), next(NULL), right(NULL){ }
        int index;
        Node *next;
        Chain *right;
};

class Chain{
    public:
        Chain() : first(NULL), joker(0){ }
        void print(){
            Node* cur = this->first;
            while(cur != NULL){
                cout << cur->index;
                if(cur->next != NULL) cout << ' ';
                cur = cur->next;
            }
            cout << endl;
        }
        Node* first;
        int joker;
};

Chain* create_chain(int n, int cir){ 
    Chain *newchain = new Chain();
    Node *cur, *newnode;
    for(int a = 1 ; a <= n ; a++){
        newnode = new Node(a);
        if(a == 1) newchain->first = cur = newnode;
        else cur = cur->next = newnode;
    }
    if(cir) cur->next = newchain->first;
    return newchain;
}

int main(){
    int N, M, K;
    int i, j;
    int index;
    cin >> N >> M >> K;

    int Joker[N+1] = {0};

    //joker
    for(int a = 0 ; a < K ; a++){
        cin >> index;
        Joker[index] = 1;
    }

    //player
    Chain *chain = create_chain(N, 1);
    Node *cur = chain->first, *A, *B, *temp;

    //cards
    for(int a = 1 ; a <= N ; a++){
        Chain *player = create_chain(M, 0);
        if(Joker[a]) player->first->index = -1;
        player->joker = Joker[a];
        cur->right = player;
        cur->index = M;
        cur = cur->next;
    }

    cur = chain->first;

    //game
    while(cin >> i >> j){
        if(i == -1 && j == -1) break;
        //player
        A = cur->right->first, B = cur->next->right->first;
        i = (i > cur->next->index) ?cur->next->index :i;
	j = (j > cur->index) ?cur->index + 1 :j;
        //delete
        if(i == 1){
	    cur->next->right->first = B->next;
        }else{
            while(i-- > 1) temp = B, B = B->next;
            temp->next = B->next;
        }
        //insert
        if(j == 1){
            cur->right->first = B;
            B->next = A;
        }else{
            while(j-- > 2) A = A->next;
            B->next = A->next;
            A->next = B;
        }
        //joker
        if(B->index == -1){
            cur->right->joker++;
            cur->next->right->joker--;
        }
        //cards
        cur->index++;
	cur->next->index--;
        cur = cur->next;
    }
    //print
    cur = chain->first;
    while(cur->right->joker) cur = cur->next;
    cur->right->print();
}
