#include <iostream>
#include <string>
#include "function.h"
//#include "13182.h"
using namespace std;

Guest::Guest(){  //constructor
    this->name = "";
    this->money = 0;
    this->skill = 0;
}
Guest::Guest(string s, int m, int ski){
    this->name = s;
    this->money = m;
    this->skill = ski;
}
Guest::~Guest() = default;
string Guest::get_name(){
    return this->name;
}
int Guest::get_money(){
    return this->money;
}
int Guest::get_skill(){
    return this->skill;
}
void Guest::Win(int m){
    this->money += m;
}

Casino::Casino(){
    fee = income = guest_num = list_num = 0;
    for(int i = 0 ; i < 1009 ; i++){
        guest[i] = nullptr;
        blacklist[i] = "";
    }
}
Casino::~Casino(){
    for(int i = 0 ; i < 1009 ; i++){
        if(guest[i]) {
            delete guest[i];
            guest[i] = nullptr;
        }
    }
}
void Casino::Enterance(int f){
    fee = f;
}
void Casino::GuestEnter(string s, int m, int ski){
    for(int i = 0 ; i < list_num ; i++){
        if(blacklist[i] == s) return;  //blacklist
    }
    for(int i = 0 ; i < guest_num ; i++){
        if(guest[i]) if(guest[i]->get_name() == s) return; //inside
    }
    if(m - fee <= 0){
        income += m;
        blacklist[list_num++] = s;
        return;  //bankrupt
    }
    //enter
    income += fee;
    Guest *newguest = new Guest(s, m - fee, ski);
    for(int i = 0 ; i < guest_num ; i++){
        if(!guest[i]){
            guest[i] = newguest;
            return;
        }
    }
    guest[guest_num++] = newguest;
    return;
}
void Casino::Win(string s, int m){
    for(int i = 0 ; i < list_num ; i++){
        if(blacklist[i] == s) return;  //blacklist
    }
    for(int i = 0 ; i < guest_num ; i++){
        if(guest[i]){
            if(guest[i]->get_name() == s){
                int skill = guest[i]->get_skill();
                int money = guest[i]->get_money();
                if(m > 2 * skill){  //cheat
                    income -= m;
                    blacklist[list_num++] = s;
                    delete guest[i];
                    guest[i] = nullptr;
                    //guest_num--;
                    return;
                }
                else if(money + m <= 0){  //bankrupt
                    income += money;
                    blacklist[list_num++] = s;
                    delete guest[i];
                    guest[i] = nullptr;
                    //guest_num--;
                    return;
                }
                else{
                    income -= m;
                    guest[i]->Win(m);
                    return;
                }
            }
        }
    }
}
void Casino::EndDay(){
    for(int i = 0 ; i < guest_num ; i++){
        if(guest[i]) {
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