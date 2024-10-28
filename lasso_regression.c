#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "utils.h"

double *lassoRegression(double **X, size_t rows, size_t cols, double *y, double alpha, int nIterations)
{
    ;
}

int main()
{
    double alpha = 0.1;
    int nIterations = 1000;
    size_t rows = 3, cols = 2;

    // Init X
    double init_X[] = {0, 0, 1, 1, 2, 2};
    double **X = allocateMatrix(rows, cols);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            X[i][j] = init_X[i * cols + j];
        }
    }

    printf("Matrix X with %zu rows and %zu cols.\n", rows, cols);
    printMatrix(X, rows, cols, 0);

    // Init y
    double init_y[] = {0, 1, 2};
    double *y = (double *)malloc(rows * sizeof(double));
    for (int i = 0; i < rows; i++)
    {
        y[i] = init_y[i];
    }

    printf("Vector y with size %zu.\n", rows);
    printVector(y, rows, 0);

    // Ridge Loss
    double *result = lassoRegression(X, rows, cols, y, alpha, nIterations);

    // Free memory
    freeMatrix(X, rows);
    free(y);

    return 0;
}