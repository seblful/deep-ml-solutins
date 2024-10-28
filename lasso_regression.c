#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "utils.h"

void addBias(double *y, double *bias, size_t n)
{
    for (int i = 0; i < n; i++)
    {
        y[i] += bias[i];
    };
}

void calculateError(double *yTrue, double *yPred, double *errors, size_t n)
{
    for (int i = 0; i < n; i++)
    {
        errors[i] = yTrue[i] - yPred[i];
    };
}

void updateWeights(double **X, size_t rows, size_t cols, double *errors, double *weights, double alpha, double lr)
{
    for (int j = 0; j < cols; j++)
    {
        double gradient = 0;
        for (int i = 0; i < rows; i++)
        {
            gradient += X[i][j] * errors[i];
        }
        // Apply Lasso regularization: add alpha * sign(weights[j])
        double lasso_penalty = alpha * (weights[j] > 0 ? 1 : -1);
        weights[j] += lr * (gradient - lasso_penalty);
    }
}

void updateBias(double *bias, double *errors, size_t n, double lr)
{
    double bias_gradient = 0;
    for (int i = 0; i < n; i++)
    {
        bias_gradient += errors[i];
    }
    // Update bias
    *bias += lr * bias_gradient / n; // Average gradient
}

void *lassoRegression(double **X, size_t rows, size_t cols, double *yTrue, double *weights, double alpha, double lr, int nIterations)
{
    // Allocate memory

    double bias = 0;
    double *yPred = (double *)calloc(rows, sizeof(double));
    double *errors = (double *)calloc(rows, sizeof(double));

    for (int i = 0; i < nIterations; i++)
    {
        // Pred y and calculate errors
        matrixVectorMultiply(X, rows, cols, weights, cols, yPred);
        addBias(yPred, &bias, rows); // Pass address of bias
        calculateError(yTrue, yPred, errors, rows);

        // Update weights and biases
        updateWeights(X, rows, cols, errors, weights, alpha, lr);
        updateBias(&bias, errors, rows, lr);
    }

    free(yPred);
    free(errors);

    return weights; // Returning weights for further use
}

int main()
{
    double alpha = 0.1;
    double lr = 0.01;
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

    double *weights = (double *)calloc(cols, sizeof(double));
    printf("Vector weights with size %zu.\n", rows);
    printVector(weights, cols, 4);

    // Ridge Loss
    lassoRegression(X, rows, cols, y, weights, alpha, lr, nIterations);

    printf("Vector weights with size %zu.\n", cols);
    printVector(weights, cols, 4);

    // Free memory
    freeMatrix(X, rows);
    free(y);

    return 0;
}