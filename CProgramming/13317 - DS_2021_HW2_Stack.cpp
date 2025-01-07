#include<bits/stdc++.h>
using namespace std;

class Player{
    public:
        Player(int i, int h) : index(i), height(h){ }
        int index;
        int height;
};

class Stack{
    public:
        Stack() : top(-1){ }
        bool Isempty(){
            return top == -1;
        }
        void Push(Player *p){
            stack[++top] = p;
        }
        void Pop(){
            if(!Isempty()) top--;
        }
        Player* Top(){
            return stack[top];
        }
        Player *stack[200001];
        int top;
};

int main(){
    int n, h;
    cin >> n;

    int ans[n+1] = {0};
    Stack *stack = new Stack();
    Player *player;
    
    for(int i = 1 ; i <= n ; i++){
        cin >> h;
        if(stack->Isempty()) ans[i] = 0;
        else if(h > stack->Top()->height) ans[i] = stack->Top()->index;
        else{
            while(!stack->Isempty() && !ans[i]){
                if(h <= stack->Top()->height) stack->Pop();
                else ans[i] = stack->Top()->index;
            }
        }
        player = new Player(i, h);
        stack->Push(player);
    }
    //print
    for(int i = 1 ; i <= n ; i++) cout << ans[i] << ' ';
    cout << endl;
}
