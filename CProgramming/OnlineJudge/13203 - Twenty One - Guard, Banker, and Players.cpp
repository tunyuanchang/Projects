#include<iostream>
#include<sstream>
#include<string>
#include "function.h"
//#include "13203.h"
using namespace std;

int amount = 0;
Human::Human(string n, int m, int ski){
    name = n;
    money = m;
    skill = ski;
    cards = bets = 0;
    kicked = false;
}
int Human::get_money(){
    return money;
}
Human::~Human() = default;
Guard::Guard(int ski) : Human("Guard", 0, ski){ }
void Guard::Pay(Human *human){
    if(skill < human->skill){
        money -= human->skill - skill;
        human->money += human->skill - skill;
    }
}
void Guard::Kick(Human *human, int flag){
    if(flag == 1) Pay(human);
    human->kicked = true;
}
Banker::Banker(int ski) : Human("Banker", 0, ski){ }
void Banker::Pay(Human *human){
    if(human->name == "Guard"){
        money -= 100;
        human->money += 100;
    }
    else{
        amount = 0;
        amount += human->bets;
        if(human->skill < skill) amount += 10 * human->cards;
        if(human->cards == 21) amount *= 2;
        money -= amount;
        human->money += amount;
    }
}
int Banker::Win(Human *human){
    //int A = human->cards, B = cards;
    if (human->cards > 21 && cards > 21) return -1;  //nothing happend
    else if (human->cards <= 21 && (cards > 21 || human->cards > cards)) return 0;  //player win
    else if (cards <= 21 && (human->cards > 21 || cards > human->cards)) return 1;  //banker win
}
void Banker::Draw(){
    cards = 0;
    string temp;
    getline(cin, temp);
    istringstream str(temp);
    int input;
    while(str >> input) cards += input;
}
Banker::~Banker() = default;
Player::Player(string name, int m, int ski) : Human(name, m, ski){ }
void Player::Pay(Human *human){
    if(bets >= money){
        human->money += money;
        money = 0;
    }
    else{
        human->money += bets;
        money -= bets;
    }
}
void Player::Bet(){
    string temp;
    cin >> temp >> bets;
}
void Player::Draw(){
    cards = 0;
    string temp;
    cin.ignore();
    getline(cin, temp);
    istringstream str(temp);
    int input;
    while(str >> input) cards += input;
}
bool Player::Kicked(){
    return kicked;
}
bool Player::Bankrupt(){
    if(money <= 0) return true;
    return false; 
}
bool Player::Cheat(Human *human){
    if(2 * skill < amount) return true;
    return false;
}
Player::~Player() = default;