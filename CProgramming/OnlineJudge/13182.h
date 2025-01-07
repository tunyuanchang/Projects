#include <string>
using namespace std;

class Guest {
public:
	Guest();
	Guest(string s, int m, int ski);
	~Guest();
	string get_name();
	int get_money();
	int get_skill();
	void Win(int m);
	
private:
	string name;
	int money;
	int skill;
};

class Casino {
public:
	Casino();
	~Casino();
	void Enterance(int f);
	void GuestEnter(string s, int m, int ski);
	void Win(string s, int m);
	void EndDay();
	void Result();
	
private:
	int fee;
	
	int guest_num;
	Guest *guest[1009];
	
	int income;
	int list_num;
	string blacklist[1009];
};
