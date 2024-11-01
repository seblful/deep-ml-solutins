#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

double gaussSeidelIt(double **A, double *b, int n)
{
    ;
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

    return 0;
}