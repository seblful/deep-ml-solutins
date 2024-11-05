#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "utils.h"

void conjugateGradient(double **A, size_t rows, size_t cols, double *b, int n, double *result)
{
    ;
}

int main()
{
    int n = 5;
    // Initialize dimensions
    size_t rows = 2, cols = 2;

    // Initialize input data A
    double init_A[] = {4, 1, 1, 3};

    double **A = allocateMatrix(rows, cols);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            A[i][j] = init_A[i * cols + j];
        }
    }

    printf("Matrix A with %zu rows and %zu cols.\n", rows, cols);
    printMatrix(A, rows, cols, 2);

    // Init b
    double init_b[] = {1, 2};
    double *b = (double *)malloc(cols * sizeof(double));
    for (int i = 0; i < cols; i++)
    {
        b[i] = init_b[i];
    }

    printf("Vector b with size %zu.\n", cols);
    printVector(b, cols, 2);

    // Gaussian elimination
    double *result = (double *)malloc(rows * sizeof(double));
    conjugateGradient(A, rows, cols, b, n, result);

    printf("Vector result with size %zu.\n", cols);
    printVector(result, cols, 2);

    // Free memory
    freeMatrix(A, rows);
    free(b);
    free(result);

    return 0;
}