#include<stdio.h>
#include<stdlib.h>
typedef struct Mat{
    int num ;
    struct Mat *d[4] ; //link 4 direction's mat
}mat ;

mat* create(mat* pre,int dir ,int val){
    mat* MAT = (mat*)malloc(sizeof(mat)) ;
    MAT->num = val ;
    MAT->d[dir] = pre ;
    return MAT ;
}
int q,t,dir,val ;  //t type . dir direction . val value
mat *cur, *portal ; //current & portal

int main(){
    //set
    cur = portal = create(NULL,0,0) ;
    scanf("%d",&q) ;
    while(q--){
        scanf("%d",&t) ;
        switch (t){
            case 1 :
                scanf("%d%d",&dir,&val) ;
                cur->d[dir] = create(cur,(dir+2)%4,val) ; //(d+2)%4 - delta direction
                break ;
            case 2 :
                scanf("%d",&dir) ;
                cur = cur->d[dir] ;
                break ;
            case 3 :
                scanf("%d",&val) ;
                cur->num = val ;
                break ;
            case 4 :
                printf("%d\n",cur->num) ;
                break ;
            case 5 :
                portal = cur ;
                break ;
            case 6 :
                cur = portal ;
                break ;
        }
    }
}
