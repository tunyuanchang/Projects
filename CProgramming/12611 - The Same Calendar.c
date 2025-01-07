#include<stdio.h>
int t, y, Y, day ;
int prefix_d[110000]={0} ;  //prefix day
int year(int index){  //leap year
    if(index % 400 == 0 || ( index % 4 == 0 && index % 100 != 0 )) return 1 ;
    return 0 ;
}
int main(){
    for(int i=1000;i<101000;i++){
        prefix_d[i] = prefix_d[i-1] ;
        prefix_d[i] += year(i) ? 366 : 365 ;
    }
    scanf("%d",&t) ;
    while(t--){
        scanf("%d",&y) ;
        for(Y=y+1; ;Y++){
            day = prefix_d[Y] - prefix_d[y-1] ;
            if(day % 7 == 0 && year(Y+1) == year(y)) break ;
        }
        printf("%d\n",Y+1) ;
    }
}
