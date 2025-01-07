#include<iostream>
#include<string>
#include<cmath>
#include "function.h"
//#include "13172.h"

special_power::special_power(int n){
    special_power::n = n;
}
int special_power::fpow(int x){
    long long ans = x % 880301;
    for(int i = 0 ; i < n - 1 && ans != 0 ; i++){
        ans *= x;
        ans %= 880301;
    }
    return (int)ans;
}
int special_power::fpow(int x, int m){
    long long ans = x % m;
    for(int i = 0 ; i < n - 1 && ans != 0 ; i++){
        ans *= x;
        ans %= m;
    }
    return (int)ans;
}
int special_power::fpow(){
    long long ans = 2;
    for(int i = 0 ; i < n - 1 && ans != 0 ; i++){
        ans *= 2;
        ans %= 880301;
    }
    return (int)ans;
}
string special_power::fpow(string s){
    string new_s;
    for(int i = 0 ; i < s.size() ; i++){
        string sub_s(n, s[i]);
        new_s += sub_s;
    }
    return new_s;
}
string special_power::fpow(string s, int m){
    int len = 0;
    string new_s;
    for(int i = 0 ; i < s.size() && m > 0 ; i++){
        len = (m < n) ? m : n;
        string sub_s(len, s[i]);
        m -= len;
        new_s += sub_s;
    }
    return new_s;
}