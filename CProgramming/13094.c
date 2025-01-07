#include<stdio.h>
#include<stdlib.h>
#include "function.h"

Node* Create_Node(int val);

void Print_list(Node* head);

int main() {
    int N,target,split_start,split_end,val;
    scanf("%d %d %d %d",&N,&target,&split_start,&split_end);

    Node* head = NULL;
    Node* cur_node = NULL;
    for(int i=0; i<N; i++){
        scanf("%d",&val);
        Node* new_node = Create_Node(val);
        if(head==NULL){
            head = new_node;
            cur_node = new_node;
        }
        else{
            cur_node->next = new_node;
            cur_node = new_node;
        }
    }

    head = Partial_sort(head, target);
    head = Split_and_Swap(head, split_start, split_end);
    Print_list(head);
    return 0;
}

Node* Create_Node(int val)
{
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = val;
    node->next = NULL;
    return node;
}

void Print_list(Node* head)
{
    Node *temp = head;
    while(temp!=NULL){
        if(temp->next==NULL) printf("%d\n", temp->data);
		else printf("%d ", temp->data);
		temp = temp->next;
    }
}
