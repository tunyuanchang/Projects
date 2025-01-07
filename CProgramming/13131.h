#ifndef function_h
#define function_h

#include <iostream>
#include <math.h>
using namespace std;

class MAX_HEAP{
public:
    MAX_HEAP():Count(0){}
    virtual ~MAX_HEAP() {}
    virtual void PUSH(const int &) = 0;
    virtual int MAX() const = 0;
    virtual int POP() = 0;
    int count() const { return Count; }// An empty tree has height of 0. A tree with only root node has height of 1.

protected:
    int Count;
};

class Array_MAX_HEAP : public MAX_HEAP{
public:
    Array_MAX_HEAP();
    virtual ~Array_MAX_HEAP() {}
    virtual void PUSH(const int &) override; //root node is stored at index 1.
    virtual int MAX() const override;
    virtual int POP() override;

private:
    int array[1025];
};

class ListNode{
    friend class List_MAX_HEAP; //make List_BST a friend

public:
    ListNode(const int &info):value( info ),left( NULL ),right( NULL ), parent(NULL) //constructor
    {
    }//end ListNode constructor

private:
    int value;
    ListNode *left;
    ListNode *right;
    ListNode *parent;
};//end class ListNode

class List_MAX_HEAP : public MAX_HEAP{
public:
    List_MAX_HEAP();
    virtual ~List_MAX_HEAP()
    {
        deleteTree(root);
    }
    virtual void PUSH(const int &) override;
    virtual int MAX() const override;
    virtual int POP() override;

private:
    ListNode *root;
    /* clean a tree.*/
    void deleteTree(ListNode *root);
    ListNode* findparent(int cnt, ListNode* root){//find the parent of node cnt
        if(cnt <= 1) return root;
        string s = "";
        while(cnt !=0){
            s += cnt%2 +'0';
            cnt/=2;
        }ListNode *now = root;
        for(int i = 1; i < s.size()-1; i++){
            if(s[i] == '0'){
                now = now->left;
            }else{
                now = now->right;
            }
        }return now;
    }
};

#endif /* function_h */
