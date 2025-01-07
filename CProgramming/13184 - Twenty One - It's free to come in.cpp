#include <iostream>
#include <string>
#include "function.h"
//#include "13184.h"
using namespace std;

Guest::Guest(){
    name = "";
    money = skill = 0;
}
Guest::Guest(string s, int m, int ski){
    name = s;
    money = m;
    skill = ski;
}
Guest::~Guest() = default;
string Guest::get_name(){
    return name;
}
int Guest::get_money(){
    return money;
}
int Guest::get_skill(){
    return skill;
}
void Guest::Win(int m){
    money += m;
}
Casino::Casino(){
    income = guest_num = list_num = 0;
    for(int i = 0 ; i < 1009 ; i++){
        guest[i] = nullptr;
        blacklist[i] = "";
    }
}
Casino::~Casino(){
    for(int i = 0 ; i < 1009 ; i++){
        if(guest[i]){
            delete guest[i];
            guest[i] = nullptr;
        }
    }
}
void Casino::GuestEnter(string s, int m, int ski){
    for(int i = 0 ; i < guest_num ; i++){
        if(guest[i]) if(guest[i]->get_name() == s) return;
    }  //inside
    for(int i = 0 ; i < list_num ; i++){
        if(blacklist[i] == s) return;
    }  //blacklist
    Guest *new_guest = new Guest(s, m, ski);  //enter
    for(int i = 0 ; i < guest_num ; i++){
        if(!guest[i]){
            guest[i] = new_guest;
            return;
        }
    }
    guest[guest_num++] = new_guest;
    return;
}
void Casino::Win(string s, int m){
    for(int i = 0 ; i < list_num ; i++){
        if(blacklist[i] == s) return;
    }  //blacklist
    for(int i = 0 ; i < guest_num ; i++){
        if(guest[i]){
            if(guest[i]->get_name() == s){
                if(m > 2 * guest[i]->get_skill()){
                    income -= m;
                    blacklist[list_num++] = s;
                    delete guest[i];
                    guest[i] = nullptr;
                    return;
                }  //cheat
                else if(m + guest[i]->get_money() <= 0){
                    income += guest[i]->get_money();
                    blacklist[list_num++] = s;
                    delete guest[i];
                    guest[i] = nullptr;
                    return;
                }  //bankrupt
                else{
                    income -= m;
                    guest[i]->Win(m);
                    return;
                }  //win
            }
        }
    }
    return;
}
void Casino::EndDay(){
    for(int i = 0 ; i < guest_num ; i++){
        if(guest[i]){
            delete guest[i];
            guest[i] = nullptr;
        }
    }
    guest_num = 0;
}
void Casino::Result(){
    cout << income << endl;
    for(int i = 0 ; i < list_num ; i++){
        cout << blacklist[i] << endl;
    }
}