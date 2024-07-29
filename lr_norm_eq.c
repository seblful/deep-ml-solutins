#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

// Function to invert 2x2 matrix
double invertMatrix(double **matrix, double **result)
{
    // Check if matrix is not singular
    double determinant = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    if (determinant == 0)
        return 0; // Singular matrix

    // Invert matrix
    result[0][0] = matrix[1][1] / determinant;
    result[0][1] = -matrix[0][1] / determinant;
    result[1][0] = -matrix[1][0] / determinant;
    result[1][1] = matrix[0][0] / determinant;
    return 1; // Inversion successful
}

double *calculateTheta(double **X, int rows, int cols, double *y)
{
    // Create temp matrices
    double **T1 = allocateMatrix(cols, cols);
    double **IM = allocateMatrix(cols, cols);
    double **T2 = allocateMatrix(cols, rows);

    // Create temp vector
    double *theta = (double *)malloc(sizeof(double) * cols);

    // Transpose matrix
    double **X_T = transposeMatrix(X, rows, cols);

    // Multiply and inverse matrix
    matrixMultiply(X_T, cols, rows, X, rows, cols, T1);
    invertMatrix(T1, IM);
    printf("Matrix IM with %d rows and %d cols.\n", cols, cols);
    printMatrix(IM, cols, cols, 4);

    // Multiply inverse matrix on X_T and y
    matrixMultiply(IM, cols, cols, X_T, cols, rows, T2);
    matrixVectorMultiply(T2, cols, rows, y, rows, theta);

    return theta;
};

int main()
{
    // Declaration of rows and cols in A matrix
    int rows = 3, cols = 2;

    // Init X
    double **X = allocateMatrix(rows, cols);

    // Fill X
    X[0][0] = 1;
    X[0][1] = 1;
    X[1][0] = 1;
    X[1][1] = 2;
    X[2][0] = 1;
    X[2][1] = 3;

    // Print X
    printf("Matrix X with %d rows and %d cols.\n", rows, cols);
    printMatrix(X, rows, cols, 0);

    // Init y and result
    double *y = (double *)malloc(sizeof(double) * rows);
    double *theta;

    // Fill y
    y[0] = 1;
    y[1] = 2;
    y[2] = 3;

    // Print y
    printf("Vector y with size %d.\n", rows);
    printVector(y, cols, 0);

    // Calculate theta
    theta = calculateTheta(X, rows, cols, y);
    printf("Vector theta with size %d.\n", cols);
    printVector(theta, cols, 4);

    // Free memory

    return 0;
}