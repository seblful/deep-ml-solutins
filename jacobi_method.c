#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

int main()
{
    // Declaration number of linear equations, number of unknown variables
    int rows = 3, cols = 3;

    // Init matrix
    double **A = (double **)malloc(sizeof(double *) * rows);
    for (int i = 0; i < rows; i++)
    {
        A[i] = (double *)malloc(sizeof(double) * cols);
    };

    // Fill matrix
    A[0][0] = 5;
    A[0][1] = -2;
    A[0][2] = 3;

    A[1][0] = -3;
    A[1][1] = 9;
    A[1][2] = 1;

    A[2][0] = 2;
    A[2][1] = -1;
    A[2][2] = 7;

    // Print matrix
    printf("Matrix with %d rows and %d cols.\n", rows, cols);
    printMatrix(A, rows, cols, 2);

    // Init vector
    double *b = malloc(sizeof(double) * rows);

    // Fill vector
    b[0] = -1;
    b[1] = 2;
    b[2] = 3;

    // Print vector
    printf("Vector with size %d.\n", rows);
    printVector(b, rows, 2);

    return 0;
};