#include<stdio.h>
#include<stdlib.h>

typedef struct Cell{
    int num ;
    struct Cell* d[4] ;
}cell ;

int q,t ;
int dir,val ;
cell *cur ;

cell* create(cell* pre,int dir,int val){
    cell* newcell = (cell*)malloc(sizeof(cell)) ;
    newcell->num = val ;
    newcell->d[dir] = pre ;
    return newcell ;
}

int main(){
    cur = (cell*)malloc(sizeof(cell)) ;
    cur->num = 0 ;
    for(int i=0;i<4;i++) cur->d[i] = NULL ;
    scanf("%d",&q) ;
    while(q--){
        scanf("%d",&t) ;
        switch(t){
            case 1 :
                scanf("%d%d",&dir,&val) ;
                if(cur->d[dir] != NULL) printf("Invalid\n") ;
                else{
                    for(int i=0;i<4;i++){
                        if(i==(dir+2)%4) cur->d[dir] = create(cur,i,val) ;
                        if(cur->d[i] != NULL) continue ;
                        else cur->d[i] = NULL ;
                    }
                }
                break ;
            case 2 :
                scanf("%d",&dir) ;
                if(cur->d[dir] == NULL) printf("Invalid\n") ;
                else cur = cur->d[dir] ;
                break ;
            case 3 :
                scanf("%d",&cur->num) ;
                break ;
            case 4 :
                printf("%d\n",cur->num) ;
                break ;
        }
    }
}
