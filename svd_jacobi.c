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

DecompositionItem decomposeMatrix(float **A)
{
    return;
};

int main()
{
    // Declaration of result struct
    DecompositionItem result;

    // Declaration of rows and cols in A matrix
    int rows = 2, cols = 2;

    // Init matrix
    double **A = (double **)malloc(sizeof(double *) * rows);

    for (int i = 0; i < rows; i++)
    {
        A[i] = (double *)malloc(sizeof(double) * cols);
    };

    // Fill matrix
    A[0][0] = 2;
    A[0][1] = 1;
    A[1][0] = 1;
    A[1][1] = 2;

    // SVD
    result = decomposeMatrix(A);

    return 0;
};