#include<iostream>
#include "function.h"
//#include "13131.h"

int idx;
ListNode *cur, *par, *temp;
Array_MAX_HEAP::Array_MAX_HEAP(){
    for(int i = 0 ; i < 1025 ; i++) array[i] = -1;
}
void Array_MAX_HEAP::PUSH(const int &info){
    Count++;
    array[Count] = info;
    idx = Count;
    while(idx/2 >= 1){
        if(array[idx/2] < array[idx]){
            swap(array[idx/2], array[idx]);
            idx /= 2;            
        }
        else break;
    }
} //root node is stored at index 1.
int Array_MAX_HEAP::MAX() const{
    if(Count == 0) return -1;
    return array[1];
}
int Array_MAX_HEAP::POP(){
    if(Count == 0) return -1;
    int show = array[1];
    if(Count == 1){
        array[1] = -1;
        Count--;
    }
    else{
        swap(array[1], array[Count]);
        array[Count--] = -1;
        idx = 1;
        while(idx <= Count){
            if(array[idx] < array[2 * idx] || array[idx] < array[2 * idx + 1]){
                if(array[2 * idx] < array[2 * idx + 1]){
                    swap(array[idx], array[2 * idx + 1]);
                    idx = 2 * idx + 1;
                }
                else{
                    swap(array[idx], array[2 * idx]);
                    idx = 2 * idx;
                }
            }
            else break;
        }
    }
    return show;
}
List_MAX_HEAP::List_MAX_HEAP(){
    root = nullptr;
}
void List_MAX_HEAP::PUSH(const int &info){
    cur = new ListNode(info);
    Count++;
    if(Count == 1){
        root = cur;
    }
    else{
        par = findparent(Count, root);
        cur->parent = par;
        if(par->left) par->right = cur;
        else par->left = cur;
        while(cur->parent){
            if(cur->value > cur->parent->value){
                swap(cur->value, cur->parent->value);
                cur = cur->parent;
            }
            else break;
        }
    }
    return;
}
int List_MAX_HEAP::MAX() const{
    if(Count == 0) return -1;
    return root->value;
}
int List_MAX_HEAP::POP(){
    if(Count == 0) return -1;
    int show = root->value;
    if(Count == 1){
        delete root;
        root = nullptr;
        Count--;
    }
    else{
        par = findparent(Count, root), temp = nullptr;
        if(par->right) temp = par->right, par->right = nullptr;
        else temp = par->left, par->left = nullptr;
        swap(root->value, temp->value);
        delete temp;
        Count--;
        cur = root;
        int L, R;
        while(cur){
            L = (cur->left) ? cur->left->value : -1;
            R = (cur->right) ? cur->right->value : -1;
            if(cur->value < L || cur->value < R){
                if(L > R){
                    swap(cur->left->value, cur->value);
                    cur = cur->left;
                }
                else{
                    swap(cur->right->value, cur->value);
                    cur = cur->right;
                }
            }
            else break;
        }
    }
    return show;
}
void List_MAX_HEAP::deleteTree(ListNode *root){
    if(!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}