#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

int main()
{
    // Init matrices
    size_t rows = 2, cols = 2;
    double init_X[] = {1, 0, 0, 1};
    double init_Wq[] = {1, 0, 0, 1};
    double init_Wk[] = {1, 0, 0, 1};
    double init_Wv[] = {1, 2, 3, 4};
    double **X = allocateMatrix(rows, cols);
    double **Wq = allocateMatrix(rows, cols);
    double **Wk = allocateMatrix(rows, cols);
    double **Wv = allocateMatrix(rows, cols);

    // Fill matrices
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            X[i][j] = init_X[i * cols + j];
            Wq[i][j] = init_X[i * cols + j];
            Wk[i][j] = init_X[i * cols + j];
            Wv[i][j] = init_X[i * cols + j];
        };
    };

    printf("Matrix X with %d rows and %d cols.\n", rows, cols);
    printMatrix(X, rows, cols, 0);
    printf("Matrix Wq with %d rows and %d cols.\n", rows, cols);
    printMatrix(Wq, rows, cols, 0);
    printf("Matrix Wk with %d rows and %d cols.\n", rows, cols);
    printMatrix(Wk, rows, cols, 0);
    printf("Matrix Wv with %d rows and %d cols.\n", rows, cols);
    printMatrix(Wv, rows, cols, 0);

    return 0;
}