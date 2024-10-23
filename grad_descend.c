#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

int main()
{
    // Parameters
    double learning_rate = 0.01;
    int nIterations = 1000;
    int batchSize = 2;
    char method[] = "batch";

    // Init X
    size_t rows = 4, cols = 2;
    double init_X[] = {1, 1, 2, 1, 3, 1, 4, 1};
    double **X = allocateMatrix(rows, cols);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            X[i][j] = init_X[i * cols + j];
        }
    }

    printf("Matrix X with %zu rows and %zu cols.\n", rows, cols);
    printMatrix(X, rows, cols, 2);

    // Init y
    double init_y[] = {2, 3, 4, 5};
    double *y = (double *)malloc(rows * sizeof(double));
    for (int i = 0; i < rows; i++)
    {
        y[i] = init_y[i];
    }

    printf("Vector y with size %zu.\n", rows);
    printVector(y, rows, 2);

    // Initialize weights
    double *weights = (double *)calloc(cols, sizeof(double));
    printf("Vector weights with size %zu.\n", cols);
    printVector(weights, cols, 2);
}