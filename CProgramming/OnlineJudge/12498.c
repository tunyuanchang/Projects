#include<stdio.h>
#include "function.h"
int main(){
    int a, b;
    scanf("%d%d",&a,&b);
    printf("%d\n",call_add(a,b));
    return 0;
}
