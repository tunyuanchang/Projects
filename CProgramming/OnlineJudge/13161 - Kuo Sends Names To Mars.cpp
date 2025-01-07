#include<iostream>
#include<string>
using namespace std;
int a = 0;
string s;
int main(){
    cin >> s;
    for(unsigned int i = 0 ; i < s.size() - 1 ; i++){
        if(s[i] == s[i+1]){
            a++;
            s[i+1] = '@';
        }
        else if(i > 0 && s[i-1] == s[i+1]){
            a++;
            s[i+1] = '@';
        }
    }
    cout << a << endl;
}