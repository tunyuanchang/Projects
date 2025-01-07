#include<stdio.h>
int n ;
int s[105],arr[105] ;
int use[105][105] ; //use[i][j]=1 - select S1~Si j-th
int main(){
    scanf("%d",&n) ;
    for(int i=1;i<=n;i++) scanf("%d",&s[i]) ;
    arr[1]=s[1] , use[1][1]=1 ;
    for(int i=2;i<=n;i++){ //compare sum
        if(arr[i-1]>arr[i-2]+s[i]){ //not select
            arr[i]=arr[i-1] ;
            //save subproblem
            for(int j=1;j<i;j++) use[i][j]=use[i-1][j] ;
        }
        else{ //select
            arr[i]=arr[i-2]+s[i] ;
            use[i][i]=1 ;
            //save subproblem
            for(int j=1;j<i-1;j++) use[i][j]=use[i-2][j] ;
        }
    }
    for(int i=1;i<=n;i++) if(use[n][i]) printf("%d ",i) ;
}
