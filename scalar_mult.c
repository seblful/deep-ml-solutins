#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

int main()
{
    // Parameters
    double scalar = 2;

    // Init X
    size_t rows = 2, cols = 2;

    double init_X[] = {1, 2, 3, 4};
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

    // Scalar multiplication
    scalarMatrixMultiply(X, rows, cols, scalar, X);
    printf("Matrix result with %zu rows and %zu cols.\n", rows, cols);
    printMatrix(X, rows, cols, 0);

    // Free memory
    freeMatrix(X, rows);

    return 0;
}
