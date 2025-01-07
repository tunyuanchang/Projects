#include<stdio.h>
#include<stdlib.h>
#define MAX 100005
int n ;
int cnt[MAX], out[MAX], x[MAX], y[MAX], ans[MAX] ;
int* edge[MAX] ;
void dfs(int now){
    ans[now] = 1 ;
    for(int i=0; i<out[now];i++){
	dfs(edge[now][i]) ;
	    ans[now] += ans[edge[now][i]];
    }
}
int main(){
    scanf("%d", &n) ;
    for(int i=1;i<n;i++){
	scanf("%d %d",x+i ,y+i) ;
	out[x[i]] ++ ;
    }
    for(int i=1;i<=n;i++){
	edge[i] = (int*)malloc(out[i]*sizeof(int)) ;
    }
    for(int i=1;i<n;i++){
	edge[x[i]][cnt[x[i]]++] = y[i] ;
    }
    dfs(1) ;
    for(int i=1;i<=n;i++){
        printf("%d",ans[i]-1) ;
        i==n ? printf("\n") : printf(" ") ;
    }
}
