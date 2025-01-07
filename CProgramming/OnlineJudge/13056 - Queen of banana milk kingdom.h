#include<stdlib.h>
#include<string.h>

typedef struct {
	int num ;
	char *name ;
} Monkey ;

Monkey* CreateMonkeyArray(int n){
    Monkey* ptr = (Monkey*)calloc(n,sizeof(Monkey)) ;
    return ptr ;
}

void SetVal(Monkey* arr, int index, int n, char c[]){
    arr[index].num = n ;
    arr[index].name = (char*)calloc(51,sizeof(char)) ;
    strcpy(arr[index].name,c) ;
    return ;
}

int Compare(Monkey* arr, int a, int b){
    if(arr[a].num < arr[b].num) return 1 ;
    if(arr[a].num > arr[b].num) return 0 ;
    if(strcmp(arr[a].name,arr[b].name) < 0 ) return 1 ;
    if(strcmp(arr[a].name,arr[b].name) > 0 ) return 0 ;
}

void Swap(Monkey* arr, int a, int b){
    int tempn ;
    tempn = arr[a].num ,arr[a].num = arr[b].num ,arr[b].num = tempn ;
    char* tempc ;
    tempc = arr[a].name ,arr[a].name = arr[b].name ,arr[b].name = tempc ;
    return ;
}

void FreeMonkeyArray(Monkey* arr, int n){
    for(int i=0;i<n;i++) free(arr[i].name) ;
    free(arr) ;
    return ;
}
