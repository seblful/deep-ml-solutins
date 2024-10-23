#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

void calculateErrors(double *yTrue, double *yPred, size_t size, double *errors)
{
    for (int i = 0; i < size; i++)
    {
        errors[i] = yPred[i] - yTrue[i];
    }
}

void updateWeights(double *weights, double *gradient, size_t size, double lr)
{
    for (int i = 0; i < size; i++)
    {
        weights[i] = weights[i] - lr * gradient[i];
    };
}

double *gradDescent(double **X,
                    size_t rows,
                    size_t cols,
                    double *yTrue,
                    double *weights,
                    double lr,
                    int nIterations,
                    int batchSize,
                    char method[])
{

    // Declare variables
    double *yPred = (double *)malloc(rows * sizeof(double));
    double *errors = (double *)malloc(rows * sizeof(double));

    for (int i = 0; i < nIterations; i++)
    {

        if (strcmp(method, "batch") == 0)
        {
            // Predict and find error
            matrixVectorDotProduct(X, rows, cols, weights, cols, yPred);
            calculateErrors(yTrue, yPred, rows, errors);

            // Calculate gradient
            double **X_T = transposeMatrix(X, rows, cols);
            double *gradient = (double *)malloc(cols * sizeof(double));
            matrixVectorDotProduct(X_T, cols, rows, errors, rows, gradient);
            scalarVectorMultiply(gradient, cols, 2 / (double)rows);

            // Update weights
            updateWeights(weights, gradient, cols, lr);
            ;
        };
    }

    return weights;
}

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

    // Gradient descent
    double *updWeights = gradDescent(X, rows, cols, y, weights, learning_rate, nIterations, batchSize, method);
    printf("Vector updWeights with size %zu.\n", cols);
    printVector(updWeights, cols, 2);

    return 0;
}