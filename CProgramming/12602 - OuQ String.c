#include <stdio.h>
int k ;
long long l,r ;
long long len[51] = {0} ;
char str[5] = "OuQ" ;
char solve(int K,long long index){
    if(K == 1)
        return str[index] ;
    //first
    if(index == 0)
        return 'O' ;
    //middle
    else if(index == len[K-1]+1)
        return 'u' ;
    //end
    else if(index == len[K]-1)
        return 'Q' ;
    else{
        //middle left
        if(index < len[K-1]+1) solve(K-1,index-1) ;
        //middle right
        else solve(K-1,index-1-len[K-1]-1) ;
    }
}
int main(){
    for(int i=1;i<51;i++) len[i] = 2 * len[i-1] + 3 ;
    while(scanf("%d %lld %lld\n",&k,&l,&r) != EOF){
        for(long long i=l;i<=r;i++) printf("%c",solve(k,i)) ;
        printf("\n") ;
    }
}
