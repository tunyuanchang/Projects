struct Node{
    Node *prev;
    Node *next;
    int val;
    int tag;
};

class KuoYangPresent {
public:
	KuoYangPresent(int k);
	void Push(int x);
	void Pop();
	void ProgrammingTanoshi();
	void KuoYangTeTe();
	void PrintList(); 
	
private:
	Node *head, *mid, *tail;
	int sz, k;
};

