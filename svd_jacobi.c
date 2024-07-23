#include <stdlib.h>
#include <stdio.h>
#include <math.h>

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
    double **A_T, **A_T_A, **J, **J_T, **A_temp, **A_prime;
    A_T = allocateMatrix(cols, rows);
    A_T_A = allocateMatrix(rows, rows);
    J = allocateMatrix(rows, cols);
    J_T = allocateMatrix(cols, rows);
    A_temp = allocateMatrix(cols, rows);
    A_prime = allocateMatrix(cols, cols);

    // Declaration of vector
    double *E;

    // Declaration of numbers
    double theta;

    // Transpose matrix
    A_T = transposeMatrix(A, rows, cols);
    printf("Matrix A_T with %d rows and %d cols.\n", cols, rows);
    printMatrix(A_T, cols, rows, 2);

    // Multiply matrix
    matrixMultiply(A, cols, rows, A_T, rows, cols, A_T_A);
    printf("Matrix A_T_A with %d rows and %d cols.\n", rows, rows);
    printMatrix(A_T_A, cols, cols, 2);

    // Calculate theta
    theta = 0.5 * atan2(2 * A_T_A[0][1], A_T_A[0][0] - A_T_A[1][1]);
    printf("Theta is %f.\n", theta);

    // Fill J
    J[0][0] = cos(theta);
    J[0][1] = -sin(theta);
    J[1][0] = sin(theta);
    J[1][1] = cos(theta);

    // Print J
    printf("Matrix J with %d rows and %d cols.\n", rows, cols);
    printMatrix(J, rows, cols, 3);

    // Transpose K
    J_T = transposeMatrix(J, rows, cols);

    // Calculate A_prime
    matrixMultiply(J_T, cols, rows, A_T_A, rows, rows, A_temp);
    matrixMultiply(A_temp, cols, rows, J, rows, cols, A_prime);
    printf("Matrix A_prime with %d rows and %d cols.\n", cols, cols);
    printMatrix(A_prime, cols, cols, 2);

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