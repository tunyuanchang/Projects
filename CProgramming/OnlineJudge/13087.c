#include <stdio.h>
#include <stdlib.h>
#include "function.h"
void traversal(Node* head);

int main(){
    int T,M,inst,i;
    int val,idx1,idx2,k;
    scanf("%d%d", &T,&M);
    Node* head = NULL;
    int *array = (int*)malloc(sizeof(int)*M);
    for(i=0; i<M; ++i){
        scanf("%d",&array[i]);
    }
    if(M > 0){
        head = createList(array, M);
        traversal(head);
    }
    while(T--){
        scanf("%d",&inst);
        if(inst == 0){ // insert
            scanf("%d",&val);
            push_front(&head, val);
        }else if(inst == 1){ // copy link list
            Node* otherHead = copyList(head);
            /* free original list*/
            while(head != NULL){
                Node* temp = head;
                head = head->next;
                free(temp);
            }
            head = otherHead;
        }else if(inst == 2){ // delete element
            scanf("%d",&val);
            deleteElementByIdx(&head, val);
        }else if(inst == 3){ // swap link element
            scanf("%d%d",&idx1, &idx2);
            SwapElementByIdx(&head,idx1,idx2);
        }
        else if(inst == 4){ // reverse list
            ReverseList(&head);
        }
        else if(inst == 5){ //shift list by k
            scanf("%d",&k);
            ShiftListByK(&head,k);
        }
        traversal(head);
    }
    /* free linked list*/
    while(head != NULL){
        Node* temp = head;
        head = head->next;
        free(temp);
    }
    return 0;
}
void traversal(Node* head){
    if(head == NULL)
        return;
    while(head != NULL){
        printf("%d ", head->data);
        head = head->next;
    }printf("\n");
}
