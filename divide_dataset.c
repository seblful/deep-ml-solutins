#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

int main()
{
    // Init variavles
    size_t feature_i = 0;
    size_t threshold = 5;

    // Init X
    size_t rows = 5, cols = 2;
    double init_X[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    double **X = allocateMatrix(rows, cols);
    // Fill x
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            X[i][j] = init_X[i * cols + j];
        };
    };

    printf("Matrix X with %d rows and %d cols.\n", rows, cols);
    printMatrix(X, rows, cols, 0);
}