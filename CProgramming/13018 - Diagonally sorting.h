#define swap(a,b) {a^=b;b^=a;a^=b;}
#define min(a,b) (((a)<(b)) ?(a) :(b))
void sort(long long arr[][500],int row,int col,int n){
    for(int i=0;i<n-1;i++)
        for(int j=0;j<n-1-i;j++)
            if(arr[row+j][col+j]>arr[row+j+1][col+j+1])
                swap(arr[row+j][col+j],arr[row+j+1][col+j+1]) ;
}
void array2d_sort(int row, int col, long long arr[][500]){
    //lower left
    for(int i=0;i<row;i++) sort(arr,i,0,min(row-i,col)) ;
    //upper right
    for(int j=0;j<col;j++) sort(arr,0,j,min(row,col-j)) ;
}
