#include <stdlib.h>
#include <stdio.h>

#include "utils.h"

// Output struct
typedef struct
{
    double **U;
    double *E;
    double **V;
} DecompositionItem;

DecompositionItem decomposeMatrix(double **A, int rows, int cols)
{
    // Declaration and initialization of matrices
    double **A_T, **A_T_A;
    A_T = allocateMatrix(cols, rows);
    A_T_A = allocateMatrix(cols, cols);

    // Transpose matrix
    A_T = transposeMatrix(A, rows, cols);
    printf("Matrix A_T with %d rows and %d cols.\n", cols, rows);
    printMatrix(A_T, cols, rows, 2);

    // Multiply matrix
    matrixMultiply(A_T, cols, rows, A, rows, cols, A_T_A);
    printf("Matrix A_T_A with %d rows and %d cols.\n", cols, cols);
    printMatrix(A_T_A, cols, cols, 2);

    // Declaration of vector
    double *E;

    return;
};

int main()
{
    // Declaration of result struct
    DecompositionItem result;

    // Declaration of rows and cols in A matrix
    int rows = 2, cols = 2;

    // Init matrix
    double **A;

    A = allocateMatrix(rows, cols);

    // Fill matrix
    A[0][0] = 2;
    A[0][1] = 1;
    A[1][0] = 1;
    A[1][1] = 2;

    // Print matrix
    printf("Matrix A with %d rows and %d cols.\n", rows, cols);
    printMatrix(A, rows, cols, 2);

    // SVD
    result = decomposeMatrix(A, rows, cols);

    return 0;
};