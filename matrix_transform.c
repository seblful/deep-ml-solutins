#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

int main()
{
    // Init matrices
    size_t rows = 2, cols = 2;

    double init_A[] = {1, 2, 3, 4};
    double init_T[] = {2, 0, 0, 2};
    double init_S[] = {1, 1, 0, 1};
    double **A = allocateMatrix(rows, cols);
    double **T = allocateMatrix(rows, cols);
    double **S = allocateMatrix(rows, cols);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            A[i][j] = init_A[i * cols + j];
            T[i][j] = init_T[i * cols + j];
            S[i][j] = init_S[i * cols + j];
        }
    }

    printf("Matrix A with %zu rows and %zu cols.\n", rows, cols);
    printMatrix(A, rows, cols, 0);
    printf("Matrix T with %zu rows and %zu cols.\n", rows, cols);
    printMatrix(T, rows, cols, 0);
    printf("Matrix S with %zu rows and %zu cols.\n", rows, cols);
    printMatrix(S, rows, cols, 0);

    // Transform matrix

    // Free memory
    freeMatrix(A, rows);
    freeMatrix(T, rows);
    freeMatrix(S, rows);

    return 0;
}