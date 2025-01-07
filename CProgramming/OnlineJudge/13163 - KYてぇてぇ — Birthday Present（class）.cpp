#include<iostream>
#include "function.h"
//#include "13163.h"

using namespace std;
int TAG = 0;

KuoYangPresent::KuoYangPresent(int k){  //constructor
    sz = 0;
    KuoYangPresent::k = k;
    head = mid = tail = NULL;
}
void KuoYangPresent::Push(int x){
    Node *newnode = new Node;
	newnode->prev = newnode->next = NULL;
	newnode->val = x;
	newnode->tag = TAG;
    if(sz == 0) mid = tail = NULL;
    if(!head || !tail) head = tail = mid = newnode;
    else{
        newnode->prev = tail;
        tail = tail->next = newnode;
        if(sz % 2 == 0) mid = mid->next;
    }
    sz++;
}
void KuoYangPresent::Pop(){
    if(sz == 0) return;
    Node *temp = mid;
    if(sz % 2){
        if(sz == 1) head = mid = NULL;
        else mid = mid->prev;
    }
    else{
        if(sz == 2) head = mid = head->next, head->prev = NULL;
        else mid = mid->next;
    }
    if(temp->prev != NULL) temp->prev->next = temp->next;
    if(temp->next != NULL) temp->next->prev = temp->prev;
    delete temp;
    sz--;
}
void KuoYangPresent::ProgrammingTanoshi(){
    TAG++;
}
void KuoYangPresent::KuoYangTeTe(){
    if(TAG == 0 || sz == 0) return;
    Node *temp = head ;
    while(temp){
        if(temp->tag < TAG) temp->val %= k;
        temp = temp->next;
    }
}
void KuoYangPresent::PrintList(){
    if(sz == 0) return;
    Node *temp = head ;
    while(temp){
        cout << temp->val << ' ';
        temp = temp->next;
    }
    cout << endl;
}