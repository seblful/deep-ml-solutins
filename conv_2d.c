#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "utils.h"

int main()
{
    int padding = 0, stride = 1;

    // Init X
    size_t rows = 5, cols = 5;
    double init_X[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 18, 18, 19, 20, 21, 22, 23, 24, 25};
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

    // Init kernel
    size_t k_rows = 2, k_cols = 2;
    double init_K[] = {1, 2, 3, -1};
    double **K = allocateMatrix(k_rows, k_cols);
    for (int i = 0; i < k_rows; i++)
    {
        for (int j = 0; j < k_cols; j++)
        {
            K[i][j] = init_K[i * k_cols + j];
        }
    }

    printf("Matrix K with %zu rows and %zu cols.\n", k_rows, k_cols);
    printMatrix(K, k_rows, k_cols, 1);
}