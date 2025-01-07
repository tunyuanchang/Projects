#include <bits/stdc++.h>
using namespace std;

class Node{
    public:
        Node(int value) : index(value), next(NULL){ }
        int index;
        Node *next;
};

class Chain{
    public:
        Chain() : first(NULL){ }
        Node *first;
};

int main(){
    Chain *chain = new Chain();
    Node *newnode, *cur, *bomber;
    int N, k, i;
    unsigned long long j;  //2^64 - 1
    cin >> N;
    for(int i = 0 ; i < N ; i++){
        cin >> k;
        newnode = new Node(k);
        if(i == 0) chain->first = cur = newnode;
        else cur = cur->next = newnode;
    }
    cur = cur->next = chain->first;

    while(cin >> i){
        if(i == -1) break;
        if(i == 1){  //pass
            cin >> j;
            j = (j - 1 + N) % N;
            while(j-- > 0) cur = cur->next;
            bomber = cur->next;
            cur->next = cur->next->next;
            cur = bomber->next;
            delete bomber;
            bomber = NULL;
            N--;
            if(N == 1) break;
        }else{  //add
            cin >> k;
            newnode = new Node(k);
            newnode->next = cur->next;
            cur->next = newnode;
            N++;
        }
    }
    for(int i = 0 ; i < N ; i++){
        if(i != N - 1) cout << cur->index << ' ';
        else cout << cur->index << endl;
        cur = cur->next;
    }
}
