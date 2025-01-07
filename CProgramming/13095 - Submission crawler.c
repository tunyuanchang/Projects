#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define maxid 100005
#define maxchar 105

typedef struct{
    int count,penalty,status ;
}Data ;
typedef struct User{
    int id,count,penalty ;  //count times
    Data *submission ;
    struct User *next ;
}User ;

char input[maxchar] ;

int space(int ) ;
User* create(int ) ;
int cmp(const void* ,const void* ) ;

int main(){
    int start = 0 ;
    User **user, **ans ;
    user = (User**)malloc(maxid*sizeof(User*)) ;
    ans = (User**)malloc(maxid*sizeof(User*)) ;
    for(int i=0;i<10;i++) fgets(input,maxchar,stdin) ; //first 10 lines
    while(1){ //input until end
        fgets(input,maxchar,stdin) ;
        start = space(0) ;
        if(strncmp(input+start,"</tbody>",8)==0) break ; //end
        else if (strncmp(input+start,"<tr>",4)==0){ //each case
            int hr,min,time,ID,PROBLEM,STATUS ;
            for(int i=0;i<4;i++){
                fgets(input,maxchar,stdin) ;
                start = space(space(0) + 4) ;
                if(i==0){
                    hr = atoi(input+start) ;
                    min = atoi(input+start+3) ;
                    time = 60*hr + min ;
                }
                else if(i==1){
                    ID = atoi(input+start) ;
                }
                else if(i==2){
                    PROBLEM = input[start]-'A' ;
                }
                else if(i==3){
                    if(input[start]=='A') STATUS = 1 ;
                    else STATUS = 0 ;
                }
            }
            Data *cur ; //save data
            if(user[ID]==NULL) user[ID] = create(ID) ;
            cur = &(user[ID]->submission[PROBLEM]) ;
            if(cur->status==0){
                if(STATUS==1){
                    cur->status = 1 ;
                    cur->penalty = 20 * cur->count + time ;
                    user[ID]->count++ ;
                    user[ID]->penalty += cur->penalty ;
                }
                cur->count++ ;
            }
        }
    }
    int size = 0 ;
    for(int i=0;i<maxid;i++){
        if(user[i]!=NULL) ans[size++] = user[i] ;
    }
    qsort(ans,size,sizeof(User*),cmp) ;
    //output
    for(int i=0;ans[i]!=NULL;i++){
        printf("%d ",ans[i]->id);
        for(int j=0;j<10;j++){
            Data* cur = &(ans[i]->submission[j]) ;
            if(cur->count==0) printf("-") ;  //not submit
            else printf("%d",cur->count) ;
            printf("/") ;
            if(cur->status==0) printf("-") ;  //not ac
            else printf("%d",cur->penalty) ;
            printf(" ") ;
        }
        printf("%d %d\n",ans[i]->count,ans[i]->penalty) ;
    }
}
int space(int idx){ //skip space
    while(input[idx] == ' ') idx++ ;
    if(input[idx] == '\0') return -1 ;
    else return idx ;
}
User* create(int idx){ //create newuser
    User *newuser = (User*)malloc(sizeof(User)) ;
    newuser->id = idx ;
    newuser->submission = (Data*)malloc(10*sizeof(Data)) ;
    return newuser ;
}
int cmp(const void* a,const void* b){
    User *x = *(User**)a, *y = *(User**)b ;
    if(x->count < y->count) return 1 ;
    if(x->count > y->count) return -1 ;
    if(x->penalty > y->penalty) return 1 ;
    if(x->penalty < y->penalty) return -1 ;
    if(x->id > y->id) return 1 ;
    if(x->id < y->id) return -1 ;
    return 0 ;
}
