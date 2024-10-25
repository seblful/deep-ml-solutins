#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

int main()
{
    // Init A
    size_t rowsA = 2, colsA = 2;

    double init_A[] = {1, 2, 2, 4};
    double **A = allocateMatrix(rowsA, colsA);
    for (int i = 0; i < rowsA; i++)
    {
        for (int j = 0; j < colsA; j++)
        {
            A[i][j] = init_A[i * colsA + j];
        }
    }

    printf("Matrix A with %zu rows and %zu cols.\n", rowsA, colsA);
    printMatrix(A, rowsA, colsA, 0);

    // Init B
    size_t rowsB = 2, colsB = 2;

    double init_B[] = {2, 1, 3, 4};
    double **B = allocateMatrix(rowsB, colsB);
    for (int i = 0; i < rowsB; i++)
    {
        for (int j = 0; j < colsB; j++)
        {
            B[i][j] = init_B[i * colsB + j];
        }
    }

    printf("Matrix B with %zu rows and %zu cols.\n", rowsB, colsB);
    printMatrix(B, rowsB, colsB, 0);

    // Allocate result matrix
    double **result = allocateMatrix(rowsA, colsB);

    // Perform multiplication
    matrixMultiply(A, rowsA, colsA, B, rowsB, colsB, result);

    printf("Matrix result with %zu rows and %zu cols.\n", rowsA, colsB);
    printMatrix(result, rowsA, colsB, 0);

    // Free memory
    freeMatrix(A, rowsA);
    freeMatrix(B, rowsB);
    freeMatrix(result, rowsA);

    return 0;
}