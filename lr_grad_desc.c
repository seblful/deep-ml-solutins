#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

double *gradientDescent(double **X, int rows, int cols, double *y, double *theta, double alpha, int iterations)
{
    for (int iter = 0; iter < iterations; iter++)
    {
        double *grad = (double *)malloc(cols * sizeof(double));

        // Initialize gradient to zero
        for (int j = 0; j < cols; j++)
        {
            grad[j] = 0;
        }

        // Calculate gradient
        for (int i = 0; i < rows; i++)
        {
            double prediction = 0;
            for (int j = 0; j < cols; j++)
            {
                prediction += X[i][j] * theta[j];
            }
            double error = prediction - y[i];
            for (int j = 0; j < cols; j++)
            {
                grad[j] += (error * X[i][j]) / rows;
            }
        }

        // Update theta
        for (int j = 0; j < cols; j++)
        {
            theta[j] -= alpha * grad[j];
        }

        free(grad);
    }

    return theta;
};

int main()
{
    // Declaration of rows and cols in X matrix
    int rows = 3, cols = 2;

    // Init X
    double **X = allocateMatrix(rows, cols);

    // Fill X
    X[0][0] = 1;
    X[0][1] = 1;
    X[1][0] = 1;
    X[1][1] = 2;
    X[2][0] = 1;
    X[2][1] = 3;

    // Print X
    printf("Matrix X with %d rows and %d cols.\n", rows, cols);
    printMatrix(X, rows, cols, 0);

    // Init y and result
    double *y = (double *)malloc(sizeof(double) * rows);
    double *theta = (double *)malloc(sizeof(double) * rows);

    // Fill y
    y[0] = 1;
    y[1] = 2;
    y[2] = 3;

    // Fill theta
    for (int i = 0; i < cols; i++)
    {
        theta[i] = 0;
    }

    // Print y, theta
    printf("Vector y with size %d.\n", rows);
    printVector(y, rows, 0);

    printf("Vector theta with size %d.\n", cols);
    printVector(theta, cols, 0);

    // Init numbers
    double alpha = 0.01;
    int iterations = 1000;

    // Perform gradient descent
    theta = gradientDescent(X, rows, cols, y, theta, alpha, iterations);

    // Print final theta
    printf("Final coefficients (theta):\n");
    printVector(theta, cols, 4);

    // Free allocated memory
    freeMatrix(X, rows);
    free(y);
    free(theta);

    return 0;
};