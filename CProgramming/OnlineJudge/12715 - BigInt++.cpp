#include<cstring>
#include "function.h"
//#include "12715.h"
void swap(char *a, char *b){
    char t;
    t = *a;
    *a = *b;
    *b = t;
}
void reverse(char *s){
    int len = strlen(s);
    for(int i = 0 ; i < len / 2 ; i++) swap(&(s[i]), &(s[len - 1 - i]));
}
namespace oj{
    BigInt::BigInt(char *s){
        _val = new char[1024]{'\0'};
        strcpy(_val, s);
    }
    BigInt::~BigInt(){
        delete _val;
    }
    BigInt& BigInt::operator++(){
        //add 1
        reverse(_val);
        int len = strlen(_val);
        _val[0] += 1;
        for(int i = 0 ; i < len ; i++){
            if(_val[i] > '9'){
                _val[i] = '0';
                if(i == len - 1) _val[len++] = '1';
                else _val[i + 1] += 1;
            }
            else break;
        }
        _val[len + 1] = '\0';
        reverse(_val);

        return (*this);
    }
    BigInt BigInt::operator++(int){
        BigInt copy(_val);
        //add 1
        reverse(_val);
        int len = strlen(_val);
        _val[0] += 1;
        for(int i = 0 ; i < len ; i++){
            if(_val[i] > '9'){
                _val[i] = '0';
                if(i == len - 1) _val[len++] = '1';
                else _val[i + 1] += 1;
            }
            else break;
        }
        _val[len + 1] = '\0';
        reverse(_val);

        return copy;
    }
    BigInt& BigInt::operator--(){
        //sub 1
        reverse(_val);
        int len = strlen(_val);
        if(len != 1 || _val[0] != '0'){
            _val[0] -= 1;
            for(int i = 1 ; i < len ; i++){
                if(_val[i - 1] < '0'){
                    _val[i - 1] = '9';
                    _val[i] -= 1;
                }
                else break;
            }
            for(int i = len - 1 ; i > 0 ; i--){
                if(_val[i] == '0') _val[i] = '\0';
                else break;
            }
        }
        reverse(_val);

        return (*this);
    }
    BigInt BigInt::operator--(int){
        BigInt copy(_val);
        //sub 1
        reverse(_val);
        int len = strlen(_val);
        if(len != 1 || _val[0] != '0'){
            _val[0] -= 1;
            for(int i = 1 ; i < len ; i++){
                if(_val[i - 1] < '0'){
                    _val[i - 1] = '9';
                    _val[i] -= 1;
                }
                else break;
            }
            for(int i = len - 1 ; i > 0 ; i--){
                if(_val[i] == '0') _val[i] = '\0';
                else break;
            }
        }
        reverse(_val);

        return copy;
    }
    char* BigInt::to_s(){
        return _val;
    }
}