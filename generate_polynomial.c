#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

int main()
{
    // Init variavles
    int degree = 2;

    // Init X
    size_t rows = 3, cols = 2;
    double init_X[] = {2, 3, 3, 4, 5, 6};
    double **X = allocateMatrix(rows, cols);

    // Fill X
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