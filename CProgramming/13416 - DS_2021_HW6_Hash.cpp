#ifndef FUNCTION_H
#define FUNCTION_H
#include <vector>
#include <list>
#include <iostream>
#include <string>
//#include "function.h"
using namespace std;
#define SIZE 41

int val, base = 13331 % SIZE;

void Implement::Add(const string &str){
    val = 0;
    for(char c: str) val = (val * base + int(c)) % SIZE;

    for(string s: this->table[val])
        if(s == str) return;

    this->table[val].push_back(str);
    return;
}
void Implement::Delete(const string &str){
    val = 0;
    for(char c: str) val = (val * base + int(c)) % SIZE;
    
    for(auto it = this->table[val].begin() ; it != this->table[val].end() ; it++)
        if(*it == str){
            this->table[val].erase(it);
            return;
        }
    
    return;
}
bool Implement::Exist(const string &str){
    val = 0;
    for(char c: str) val = (val * base + int(c)) % SIZE;
    
    for(string s: this->table[val])
        if(s == str) return true;

    return false;
}
#endif
