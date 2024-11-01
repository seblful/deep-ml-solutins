#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

void gaussSeidelIt(double **A, size_t rows, size_t cols, double *b, double *x)
{
    for (size_t i = 0; i < rows; i++)
    {
        double sum = b[i];
        for (size_t j = 0; j < cols; j++)
        {
            if (i != j)
            {
                sum -= A[i][j] * x[j];
            }
        }
        x[i] = sum / A[i][i];
    }
}

void gaussSeidel(double **A, size_t rows, size_t cols, double *b, int iterations, double *x)
{
    for (int k = 0; k < iterations; k++)
    {
        gaussSeidelIt(A, rows, cols, b, x);
    }
}

int main()
{
    // Initialize dimensions
    size_t rows = 3, cols = 3;

    // Initialize input data A
    double init_A[] = {4, 1, 2, 3, 5, 1, 1, 1, 3};

    double **A = allocateMatrix(rows, cols);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            A[i][j] = init_A[i * cols + j];
        }
    }

    printf("Matrix A with %zu rows and %zu cols.\n", rows, cols);
    printMatrix(A, rows, cols, 0);

    // Init b
    double init_b[] = {4, 7, 3};
    double *b = (double *)malloc(cols * sizeof(double));
    for (int i = 0; i < cols; i++)
    {
        b[i] = init_b[i];
    }

    printf("Vector b with size %zu.\n", cols);
    printVector(b, cols, 0);

    int n = 100;

    // Allocate memory for initial guess
    double *x = (double *)calloc(cols, sizeof(double));

    // Perform Gauss-Seidel iteration
    gaussSeidel(A, rows, cols, b, n, x);

    printf("Approximated solution after %d iterations:\n", n);
    printVector(x, cols, 2);

    // Free memory
    freeMatrix(A, rows);
    free(b);
    free(x);

    return 0;
}