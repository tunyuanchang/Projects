#include<string>
#include<sstream>
#include<cctype>
#include "function.h"
//#include "11014.h"
using namespace std;

void RleCodec::encode(){
    stringstream ss;
    int len = code_str.size(), start = 0;
    for(int i = 1 ; i <= len ; i++){
        if(i == len || code_str[i] != code_str[start]){  //end | reset
            if(i - start <= 2) ss << code_str.substr(start, i - start);
            else ss << i - start << code_str[start];
            //i - start = count
            start = i;
        }
    }
    code_str = ss.str();
    encoded = true;
}

void RleCodec::decode(){
    stringstream ss;
    int len = code_str.size();
    for(int i = 0 ; i < len ; i++){
        if(isdigit(code_str[i])){
            int j = i + 1;
            while(isdigit(code_str[j])) j++;
            ss << string(stoi(code_str.substr(i, j - i)), code_str[j]);
            i = j;
        }
        else{
            ss << code_str[i];
        }
    }
    code_str = ss.str();
    encoded = false;
}