#include <stdio.h>
#include <stdlib.h>
#include "function.h"

long long arr[500][500] = {};

int main(void){
    int row, col;
    scanf("%d%d", &row, &col);

    for(int i = 0; i < row; ++i)
        for(int j = 0; j < col; ++j)
            scanf("%lld", &arr[i][j]);

    array2d_sort(row, col, arr);

    for(int i = 0; i < row; ++i)
        for(int j = 0; j < col; ++j)
            printf("%lld%c", arr[i][j], (j==col-1) ? '\n' : ' ');
    
    return 0;
}
