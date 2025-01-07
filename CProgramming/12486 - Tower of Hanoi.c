#include<stdio.h>
int n ;
void honoi(char a,char c,char b,int i) ;
//move from a to c buffer b
int main(void){
    scanf("%d",&n) ;
    honoi('A','C','B',n) ;
}
void honoi(char a,char c,char b,int i){
    //move disk 1 from a to c
    if(i == 1){
        printf("move disk %d from rod %c to rod %c\n",i,a,c) ;
        return ;
    }
    //move disk 1~(i-1) from a to b
    honoi(a,b,c,i-1) ;
    //move disk i from a to c
    printf("move disk %d from rod %c to rod %c\n",i,a,c) ;
    //move disk 1~(i-1) from b to c
    honoi(b,c,a,i-1) ;
}
