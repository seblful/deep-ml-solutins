#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

int main()
{
    // Init X
    size_t rows = 2, cols = 3;

    double init_X[] = {1, 2, 3, 4, 5, 6};
    double **X = allocateMatrix(rows, cols);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            X[i][j] = init_X[i * cols + j];
        }
    }

    printf("Matrix X with %zu rows and %zu cols.\n", rows, cols);
    printMatrix(X, rows, cols, 0);

    // Transpose matrix
    double **X_T = transposeMatrix(X, rows, cols);

    printf("Matrix X_T with %zu rows and %zu cols.\n", cols, rows);
    printMatrix(X_T, cols, rows, 0);

    // Free memory
    freeMatrix(X, rows);
    freeMatrix(X_T, cols);

    return 0;
}