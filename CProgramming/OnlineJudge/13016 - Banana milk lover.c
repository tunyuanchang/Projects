#include<stdio.h>
#include<stdlib.h>
#define Max(a,b) (((a)>(b)) ?(a) :(b))
#define swap(a,b,c) {c=a ;a=b ;b=c ;}
typedef struct{
    long long sum ;
    int num,index,max ;
    int *milk ;
}group ;

int t,n ;
group *arr[2000],*temp ;

int vs(group* ,group*) ;

int main(){
    scanf("%d",&t) ;
    while(t--){
        scanf("%d",&n) ;
        //input
        for(int i=0;i<n;i++){
            arr[i]=(group* )calloc(1,sizeof(group)) ;
            arr[i]->index = i ;
            scanf("%d",&arr[i]->num) ;
            arr[i]->milk=(int* )malloc(arr[i]->num*sizeof(int)) ;
            for(int j=0;j<arr[i]->num;j++){ //element
                scanf("%d",&arr[i]->milk[j]) ;
                arr[i]->sum +=arr[i]->milk[j] ;
                arr[i]->max = Max(arr[i]->max,arr[i]->milk[j]) ;
            }
        }
        //sort
        for(int i=0;i<n;i++)
            for(int j=i+1;j<n;j++){
                if(vs(arr[i],arr[j])==1) swap(arr[i],arr[j],temp) ;
        }
        //output
        for(int i=0;i<n;i++)
            for(int j=0;j<arr[i]->num;j++){
                if(j==arr[i]->num-1) printf("%d\n",arr[i]->milk[j]) ;
                else printf("%d ",arr[i]->milk[j]) ;
            }
        //free
        for(int i=0;i<n;i++){
            free(arr[i]->milk) ;
            free(arr[i]) ;
        }
    }
}
int vs(group* a,group* b){ //0-not swap , 1-swap
    //sum
    if(a->sum > b->sum) return 0 ;
    if(a->sum < b->sum) return 1 ;
    //max
    if(a->max > b->max) return 0 ;
    if(a->max < b->max) return 1 ;
    //num
    if(a->num > b->num) return 0 ;
    if(a->num < b->num) return 1 ;
    //index
    if(a->index < b->index) return 0 ;
    if(a->index > b->index) return 1 ;
    //all same
    return 0 ;
}
