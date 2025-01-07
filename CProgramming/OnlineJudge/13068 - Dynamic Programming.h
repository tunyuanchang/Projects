int cmp(const void* a, const void* b){
    int x = *(int* )a ;
    int y = *(int* )b ;
    if(x < y) return 1 ;
    if(x == y) return 0 ;
    return -1 ;
}
