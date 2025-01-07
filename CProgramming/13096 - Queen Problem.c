#include<stdio.h>
#include<stdlib.h>

int n,count ;
int queen[15] ;  //queen[r]=c
long long value ;
long long arr[15][15], ans[3000] ;

void solve(int ) ;
int valid(int ,int ) ;
int cmp(const void* ,const void* ) ;
long long cal( ) ;

int valid(int r,int c){
    for(int i=0;i<r;i++){
        if(queen[i]==c || queen[i]==c+r-i || queen[i]==c-r+i) return 0 ;
    }
    return 1 ;
}
void solve(int row){
    if(row==n){
        ans[count++] = cal() ;
        return ;
    }
    for(int i=0;i<n;i++){
        if(valid(row,i)){
            queen[row] = i ;
            solve(row+1) ;
        }
    }
}
long long cal(){
    long long val = 0 ;
    for(int i=0;i<n;i++) val += arr[i][queen[i]] ;
    return val ;
}
int cmp(const void* a,const void* b){
    long long x = *(long long*)a,y = *(long long*)b ;
    if(x<y) return 1 ;
    if(x==y) return 0 ;
    if(x>y) return -1 ;
}
int main(){
    int available = 0 ;
    scanf("%d",&n) ;
    for(int i=0;i<n;i++) for(int j=0;j<n;j++) scanf("%lld",&arr[i][j]) ;
    solve(0) ;
    qsort(ans,count,sizeof(long long),cmp) ;
    for(int i=1;i<count;i++){
        if(ans[i]!=ans[0]){
            available = 1 ;
            value = ans[i] ;
            break ;
        }
    }
    available == 0 ?printf("Invalid\n") :printf("%lld\n",value) ;
}
