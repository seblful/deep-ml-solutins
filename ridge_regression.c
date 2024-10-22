#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "utils.h"

double square(double x)
{
    return x * x;
};

double ridgeLoss(double **X, size_t rows, size_t cols, double *w, double *yTrue, double alpha)
{
    double *yPred = (double *)malloc(rows * sizeof(double));
    matrixVectorDotProduct(X, rows, cols, w, cols, yPred);

    // Find sum of weights
    double weightSum = 0;
    for (int i = 0; i < cols; i++)
    {
        weightSum += square(w[i]);
    }

    // Find square differences between y
    double yDiff = 0;
    for (int i = 0; i < rows; i++)
    {
        yDiff += square(yTrue[i] - yPred[i]);
    }

    // Find loss
    double loss = (yDiff / rows) + (alpha * weightSum);

    // Free memory
    free(yPred);

    return loss;
};

int main()
{
    double alpha = 0.1;
    size_t rows = 4, cols = 2;

    // Init X
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

    // Ridge Loss
    double result = ridgeLoss(X, rows, cols, weights, y, alpha);
    printf("Ridge Loss is %0.4f.\n", result);

    // Free memory
    freeMatrix(X, rows);
    free(weights);
    free(y);

    return 0;
}