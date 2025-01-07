#include<stdio.h>
#define max 1000005
char s1[max],s2[max],temp[5] ; //s1-target s2-key
int main(){
    long long index=1,wrong=0 ;
    fgets(s1+1,max,stdin) ; //input
    while(fgets(temp,5,stdin)!=NULL){
       if(temp[0]!='\\'){
           s2[index]=temp[0] ;
           if(s1[index]!=s2[index]) wrong ++ ;
           index ++ ;
       }
       else{
           if(s1[index-1]!=s2[index-1]){
                wrong -- ;
                s2[index-1]=0 ;
           }
           if(index>1) index -- ;
       }
       if(wrong==0) printf("1\n") ;
       else printf("0\n") ;
    }
    //s1 vs s2
    int correct=1 ;
    for(int i=1;s1[i]!='\n';i++)
        if(s1[i]!=s2[i]) correct=0 ;
    if(correct==1 && wrong==0) printf("Correct\n") ;
    else printf("Incorrect\n") ;
}
