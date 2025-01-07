#include<stdlib.h>
unsigned*** new_3d_array(unsigned n,unsigned m,unsigned k){
    unsigned ***pt3 = (unsigned***)malloc(n*sizeof(unsigned**)) ;
    unsigned **pt2 = (unsigned**)malloc(n*m*sizeof(unsigned*)) ;
    unsigned *pt1 = (unsigned*)malloc(n*m*k*sizeof(unsigned)) ;
    for(unsigned i=0;i<n;i++){
        *(pt3 + i) = pt2 + i*m ;
        for(unsigned j=0;j<m;j++)
            *(pt2+ i*m + j) = pt1 + (i*m + j)*k ;
    }
    return pt3 ;
}
void delete_3d_array(unsigned ***arr){
    free(arr[0][0]) ;
    free(arr[0]) ;
    free(arr) ;
    return ;
}
