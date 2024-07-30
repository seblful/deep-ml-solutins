#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

int main()
{
    // Declaration of rows and cols in X matrix
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
    double *result;

    // Fill y
    y[0] = 1;
    y[1] = 2;
    y[2] = 3;

    // Print y
    printf("Vector y with size %d.\n", rows);
    printVector(y, rows, 0);

    // Init numbers
    double alpha = 0.01;
    int iterations = 1000;
    return 0;
};