#include <sstream>
#include <cstring>
#include <iostream>
using namespace std;

class Human {
public:
	string name;
	int money;
	int skill;
	int bets;
	int cards;

	Human(string n, int m, int ski);
	
	virtual void Pay(Human *human) {}
	virtual void Bet() {}
	void Draw();
	virtual int Win(Human *human) {}
	virtual bool Bankrupt() {}
	virtual bool Cheat(Human *human) {}
	virtual void Order(Human *banker, Human *server) {}
	
	~Human();
};

class Guard : public virtual Human {
public:
	Guard(int ski);
	void Pay(Human *human);
};

class Banker : public virtual Human {
public:
	Banker(int ski);
	void Pay(Human *human);
	int Win(Human *human);
	~Banker();
};

class Server : public virtual Human {
public:
	Server(int ski);
	~Server();
};

class Player : public virtual Human {
public:
	Player(string name, int m, int ski);
	void Pay(Human *human);
	void Bet();
	bool Bankrupt();
	bool Cheat(Human *human);
	void Order(Human *banker, Human *server);
	~Player();
};

class Casino {
public:
	Casino();
	~Casino();
	void Enterance(int f, int u);
	void Guest(string s, int m, int ski);
	void TwentyOne();
	void EndDay();
	void Result();
	
	int fee, U;
	
	Human *banker, *guard, *server;
	int player_num;
	Human *player[1009];
	
	int total_income, today_income;
	int blacklist_num;
	string blacklist[100009];
};
