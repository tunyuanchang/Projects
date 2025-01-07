int** s(int* a,int len){
    //bubble sort
    int temp ;
    for(int i=0;i<len-1;i++){ // needs n-1 passes
        for(int j=0;j<len-1-i;j++){ //Only the remaining numbers need to be compared
            if (a[j] > a[j+1]){
                temp = a[j];
                a[j] = a[j+1] ;
                a[j+1] = temp ;
            }
        }
    }
    len = sqrt(len) ;
    int** ptr = (int** )malloc(len*sizeof(int* )) ;
    for(int i=0;i<len;i++,a+=len){
        *(ptr+i)=a ;
    }
    return ptr ;
}
