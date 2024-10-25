#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "utils.h"

int main()
{
    // Init X
    size_t rows = 2, cols = 2;

    double init_X[] = {2, 1, 1, 2};
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

    double *eigenValues = findEigenValues(X, rows, cols);

    printf("Vector eigenValues with size %zu.\n", rows);
    printVector(eigenValues, rows, 2);

    // Free memory
    freeMatrix(X, rows);
    free(eigenValues);

    return 0;
}