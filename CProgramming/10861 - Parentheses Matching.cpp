#include<bits/stdc++.h>
using namespace std;

int main(){
    int n;
    string str;
    cin >> n;
    cin.ignore();
    for(int i = 1 ; i <= n ; i++){
        stack<char> match;
        bool flag = true;
        getline(cin, str);
        for(auto c : str){
            if(c == '(' || c == '{' || c == '[' || c == '<') match.push(c);
            else if(!match.empty()){
                if((match.top() == '(' && c == ')') ||
                   (match.top() == '{' && c == '}') ||
                   (match.top() == '[' && c == ']') ||
                   (match.top() == '<' && c == '>') ){
                    match.pop();
                }
                else{
                    flag = false;
                    break;
                }
            }
            else{
                flag = false;
                break;
            }
        }
        if(!match.empty()) flag = false;
        cout << "Case " << i << ": " << (flag ? "Yes" : "No") << endl;
    }
}
