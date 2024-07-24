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

void calculateSingularValues(double **A_prime, int rows, int cols, double *E)
{
    // Calculate singular values
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (i == j)
            {
                E[i] = sqrt(A_prime[i][j]);
            }
        }
    };
};

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

    // Declaration and initialization of vector
    double *E = (double *)malloc(sizeof(double) * cols);

    // Declaration of numbers
    double theta;

    // Declaration of structs
    DecompositionItem item;

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

    // Calculate singular values
    calculateSingularValues(A_prime, cols, cols, E);

    // Print singular values
    printf("Singular values: vector with size %d.\n", cols);
    printVector(E, cols, 3);

    // Write values to struct
    item.U = J;
    item.E = E;
    item.V = J_T;

    // Free memory
    freeMatrix(A_T, cols);
    freeMatrix(A_T_A, rows);
    freeMatrix(A_temp, cols);
    freeMatrix(A_prime, cols);

    return item;
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

    // Print result
    printf("Matrix U with %d rows and %d cols.\n", rows, cols);
    printMatrix(result.U, rows, cols, 3);

    printf("Vector E with size %d.\n", cols);
    printVector(result.E, cols, 3);

    printf("Matrix V with %d rows and %d cols.\n", cols, rows);
    printMatrix(result.V, cols, rows, 3);

    // Free memory
    freeMatrix(result.U, rows);
    free(result.E);
    freeMatrix(result.V, cols);

    return 0;
};