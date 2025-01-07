#include<iostream>
#include"function.h"
using namespace std;
int main(){
    int t, n;
    string x;
    cin >> t;
    while(t--){
        cin >> x >> n;
        big_number number = {x};
        if (n == 2) {
            if (number.multiple_of_two()){
                cout << "Yes\n";
            }else {
                cout << "No\n";
            }
        }
        if (n == 3) {
            if (number.multiple_of_three()){
                cout << "Yes\n";
            }else {
                cout << "No\n";
            }
        }
        if (n == 4) {
            if (number.multiple_of_four()){
                cout << "Yes\n";
            }else {
                cout << "No\n";
            }
        }
        if (n == 5) {
            if (number.multiple_of_five()){
                cout << "Yes\n";
            }else {
                cout << "No\n";
            }
        }
        if (n == 6) {
            if (number.multiple_of_six()){
                cout << "Yes\n";
            }else {
                cout << "No\n";
            }
        }
        if (n == 8) {
            if (number.multiple_of_eight()){
                cout << "Yes\n";
            }else {
                cout << "No\n";
            }
        }
        if (n == 9) {
            if (number.multiple_of_nine()){
                cout << "Yes\n";
            }else {
                cout << "No\n";
            }
        }
        if (n == 10) {
            if (number.multiple_of_ten()){
                cout << "Yes\n";
            }else {
                cout << "No\n";
            }
        }
        if (n == 11) {
            if (number.multiple_of_eleven()){
                cout << "Yes\n";
            }else {
                cout << "No\n";
            }
        }
    }
}
