#include<stdio.h>
#define maxn 501 //include 500
int n,q;
int l,r;
int ans,max;
int a[maxn];
int main(){
    //input
    scanf("%d",&n);
    for(int i = 1 ; i <= n ; i++){
        scanf("%d",&a[i]) ;
    }
    scanf("%d",&q);
    for(int t = 0 ; t < q ; t++){
        int count[maxn]={} ; //count times
        scanf("%d %d",&l,&r);
        ans = 0, max = 0; //restart
        for(int i = l ; i <= r ; i++) count[a[i]]++ ;
        for(int k = 1 ; k < maxn ; k++){
            if (count[k] > max) max = count[k], ans = k ; //find most
        }
        printf("%d\n",ans);
    }
}
