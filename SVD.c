#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

int main()
{
    // Init matrix
    int rows = 2,
        cols = 2;
    double **A = allocateMatrix(rows, cols);

    A[0][0] = -10;
    A[0][1] = 8;
    A[1][0] = 10;
    A[1][1] = -1;

    return 0;
}