#include"function.h"
#include<iostream>
using namespace std;
int main(){
    int n, a;
    Array_MAX_HEAP A_heap;
    List_MAX_HEAP B_heap;
    string s;
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> s;
        if(s == "A_push"){
            cin >> a;
            A_heap.PUSH(a);
        }else if(s == "L_push"){
            cin >> a;
            B_heap.PUSH(a);
        }
        else if(s == "max"){
            cout << A_heap.MAX() << "\n";
            cout << B_heap.MAX() << "\n";
        }
        else if(s == "A_pop"){
            cout << A_heap.POP() << "\n";
        }
        else if(s == "L_pop"){
            cout << B_heap.POP() << "\n";
        }
        else if(s == "size"){
            cout << A_heap.count() << "\n";
            cout << B_heap.count() << "\n";
        }
    }
}
