#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "utils.h"

typedef struct
{
    double *weights;
    double bias;
} LassoResult;

double sign(double x)
{
    if (x < 0)
    {
        return -1;
    }
    else if (x == 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

void addBias(double *y, double bias, size_t n)
{
    for (int i = 0; i < n; i++)
    {
        y[i] += bias;
    };
}

double calculateL1Norm(double *grad, size_t size)
{
    double sum = 0;
    for (size_t i = 0; i < size; i++)
    {
        sum += fabs(grad[i]);
    }
    return sum;
}

void calculateError(double *yTrue, double *yPred, double *errors, size_t n)
{
    for (int i = 0; i < n; i++)
    {
        errors[i] = yPred[i] - yTrue[i];
    };
}

void updateBias(double *bias, double *errors, size_t n, double lr)
{
    double bias_gradient = 0;
    for (int i = 0; i < n; i++)
    {
        bias_gradient += errors[i];
    }
    bias_gradient /= n;

    // Update bias
    *bias -= lr * bias_gradient;
}

LassoResult lassoRegression(double **X, size_t rows, size_t cols, double *yTrue,
                            double alpha, double lr, int nIterations, double tol)
{
    double bias = 0;
    double *yPred = (double *)calloc(rows, sizeof(double));
    double *weights = (double *)calloc(cols, sizeof(double));
    double *errors = (double *)calloc(rows, sizeof(double));
    double *grad_w = (double *)calloc(cols, sizeof(double));

    for (int iter = 0; iter < nIterations; iter++)
    {
        matrixVectorMultiply(X, rows, cols, weights, cols, yPred);
        addBias(yPred, bias, rows);
        calculateError(yTrue, yPred, errors, rows);

        // Calculate and store gradients
        for (int j = 0; j < cols; j++)
        {
            grad_w[j] = 0;
            for (int i = 0; i < rows; i++)
            {
                grad_w[j] += X[i][j] * errors[i];
            }
            grad_w[j] = (grad_w[j] / rows) + alpha * sign(weights[j]);
            weights[j] -= lr * grad_w[j];
        }

        updateBias(&bias, errors, rows, lr);

        // Check convergence
        if (calculateL1Norm(grad_w, cols) < tol)
        {
            break;
        }
    }

    // Fill result
    LassoResult result = {weights, bias};

    // Free memory
    free(yPred);
    free(errors);
    free(grad_w);

    return result;
}

int main()
{
    double alpha = 0.1;
    double tol = 1e-4;
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

    // Ridge Loss
    LassoResult result = lassoRegression(X, rows, cols, y, alpha, lr, nIterations, tol);

    printf("Vector weights with size %zu.\n", cols);
    printVector(result.weights, cols, 8);
    printf("Bias is %f.\n", result.bias);

    // Free memory
    freeMatrix(X, rows);
    free(result.weights);
    free(y);

    return 0;
}