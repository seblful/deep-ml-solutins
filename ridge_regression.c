#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "utils.h"

int main()
{
    double alpha = 0.1;
    size_t rows = 4, cols = 2;

    // Init X
    double init_X[] = {1, 2, 2, 1, 3, 1, 4, 1};
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

    // Init w
    double init_weights[] = {0.2, 2};
    double *weights = (double *)malloc(cols * sizeof(double));
    for (int i = 0; i < cols; i++)
    {
        weights[i] = init_weights[i];
    }

    printf("Vector weights with size %zu.\n", cols);
    printVector(weights, cols, 2);

    // Init y
    double init_y[] = {2, 3, 4, 5};
    double *y = (double *)malloc(rows * sizeof(double));
    for (int i = 0; i < rows; i++)
    {
        y[i] = init_y[i];
    }

    printf("Vector y with size %zu.\n", rows);
    printVector(y, rows, 0);
}