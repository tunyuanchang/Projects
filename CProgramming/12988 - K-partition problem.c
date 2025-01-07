#include<stdio.h>
int valid,sum,n,k ;
int a[12],use[12] ;
void solve(int ,int ,int ) ;
int main(){
    int q ;
    scanf("%d",&q) ;
    while(q--){
        //restart
        sum=valid=0 ;
        for(int i=0;i<12;i++) use[i]=0 ;
        //start
        scanf("%d%d",&n,&k) ;
        for(int i=0;i<n;i++){
            scanf("%d",&a[i]) ;
            sum +=a[i] ;
        }
        if(sum%k==0) solve(0,0,0) ;
        if(valid==1) printf("True\n") ;
        else printf("False\n") ;
    }
}
void solve(int i,int j,int count){//i index j sum count subset
    if(count==k-1){
        valid=1 ;
        return ;
    }
    if(i==n) return ;
    if(j==sum/k) solve(0,0,count+1) ;
    for(int x=0;x<2;x++){
        if(x==0) solve(i+1,j,count) ; //not choose
        else{
            if(!use[i]){
                use[i]=1 ; //denote used
                solve(i+1,j+a[i],count) ; //choose
                use[i]=0 ; //return
            }
        }
    }
}
