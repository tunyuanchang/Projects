#include <sstream>
#include <iostream>
#include <string>
#include "function.h"
//#include "13214.h"
using namespace std;

int topay = 0;

Human::Human(string n, int m, int ski){
    name = n;
    money = m;
    skill = ski;
    bets = cards = 0;
}
void Human::Draw(){
    cards = 0;
    int input;
    string temp;
    getline(cin, temp);
    istringstream ss(temp);
    while (ss >> input) cards += input;
}
Human::~Human(){ }
Guard::Guard(int ski) : Human("Guard", 0, ski){ }
void Guard::Pay(Human *human){
    if(skill < human->skill){
        money -= (human->skill - skill);
        human->money += (human->skill - skill);
    }
}
Banker::Banker(int ski) : Human("Banker", 0, ski){ }
void Banker::Pay(Human *human){
    if(human->name == "Guard"){
        money -= 100;
        human->money += 100;
        return;
    }
    else{
        topay = 0;
        topay += human->bets;
        if(human->skill < skill) topay += 10* human->cards;
        if(human->cards == 21) topay *= 2;
        money -= topay;
        human->money += topay;
    }
}
int Banker::Win(Human *human){
    if(cards > 21 && human->cards > 21) return 2;
    else if(cards <= 21 && (human->cards > 21 || cards >= human->cards)) return 1;
    else if(human->cards <= 21 && (cards > 21 || human->cards > cards))return 0;
}
Banker::~Banker(){ }
Server::Server(int ski) : Human("Server", 0, ski){ }
Server::~Server(){ }
Player::Player(string name, int m, int ski) : Human(name, m, ski){ }
void Player::Pay(Human *human){
    if(money <= bets){
        human->money += money;
        money = 0;
    }
    else{
        money -= bets;
        human->money += bets;
    }
}
void Player::Bet(){
    cin >> bets;
    cin.ignore();
}
bool Player::Bankrupt(){
    if(money <= 0) return true;
    else return false;
}
bool Player::Cheat(Human *human){
    if(topay > 3 * skill) return true;
    else return false;
}
void Player::Order(Human *banker, Human *server){
    money -= 3000;
    banker->money += 2000;
    server->money += 1000;
}
Player::~Player(){ }

Casino::Casino(){
    total_income = today_income = player_num = blacklist_num = 0;
}
Casino::~Casino(){ }
void Casino::Enterance(int f, int u){
    fee = f;
    U = u;
}
void Casino::Guest(string s, int m, int ski){
    for(int i = 0 ; i < blacklist_num ; i++){
        if(blacklist[i] == s) return;
    }//blacklist

    for(int i = 0 ; i < player_num ; i++){
        if(player[i]->name == s) return;
    }//inside
    
    if(m <= fee){
        blacklist[blacklist_num++] = s;
        return;
    }//bankrupt

    today_income += fee;
    player[player_num++] = new Player(s, m - fee, ski);
}
void Casino::TwentyOne(){
    int B, G, S; //skill
    cin >> B >> G >> S;
    banker = new Banker(B);
    guard = new Guard(G);
    server = new Server(S);
    int record[1009];
    for(int i = 0 ; i < 1009 ; i++) record[i] = 0;
    int K;
    cin >> K;
    string n;
    // check 21 player
    for(int i = 0 ; i < K ; i++){
        cin >> n;
        int flag = 1;
        Player* new_player = new Player(n, 0, 0);
        new_player->Bet();
        new_player->Draw();

        for(int j = 0 ; j < blacklist_num ; j++){
            if(blacklist[j] == n){
                flag = 0;
                break;
            }
        }//blacklist

        if(flag == 1){
            for (int j = 0 ; j < player_num ; j++){
                if (player[j]->name == n){
                    record[j] = 1;
                    player[j]->bets = new_player->bets;
                    player[j]->cards = new_player->cards;
                }
            }
        }
    }

    banker->Draw();

    for (int i = 0 ; i < player_num ; i++){
	    if (record[i] == 1){
            if(banker->Win(player[i]) == 1){
                player[i]->Pay(banker);
                if(player[i]->Bankrupt()){
                    banker->Pay(guard);
                    blacklist[blacklist_num++] = player[i]->name;
                }
            }
            else if(banker->Win(player[i]) == 0){
                banker->Pay(player[i]);
                if(player[i]->money > server->skill){
                    player[i]->Order(banker, server);
                }
                if(player[i]->Cheat(banker)){
                    banker->Pay(guard);
                    guard->Pay(player[i]);
                    blacklist[blacklist_num++] = player[i]->name;
                }
            }
        }
    }
    today_income += banker->money;
    cout << banker->money << " " << guard->money << " " << server->money << endl;
    for(int i = 0 ; i < player_num ; i++){
        if(record[i] == 1) cout << player[i]->name << " " << player[i]->money << endl;
    }
}
void Casino::EndDay(){
    total_income += today_income;
    if(today_income >= U) blacklist_num = 0;
    today_income = 0;
    player_num = 0;
    //fee = U = 0;
}
void Casino::Result(){
    cout << total_income << endl;
    for(int i = 0 ; i < blacklist_num ; i++){
        cout << blacklist[i] << endl;
    }
}