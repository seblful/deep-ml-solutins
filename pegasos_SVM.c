#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "utils.h"

typedef struct ResultSVM
{
    double *alphas;
    double beta;
} resultSVM;

double square(double x)
{
    return x * x;
}

double linearKernel(double *x, double *y, int n)
{
    double dot = 0;
    for (int i = 0; i < n; i++)
    {
        dot += x[i] * y[i];
    }

    return dot;
}

double RBFKernel(double *x, double *y, int n)
{
    double sigma = 1;

    double *v = (double *)malloc(n * sizeof(double));

    // Find difference between vectors
    for (int i = 0; i < n; i++)
    {
        v[i] = x[i] - y[i];
    }

    // Find norm of vector
    double norm = 0;
    for (int i = 0; i < n; i++)
    {
        norm += square(v[i]);
    }
    norm = sqrt(norm);

    double result = exp(-square(norm) / (2 * (square(sigma))));

    return result;
};

resultSVM pegasosKernelSVM(double **data, int rows, int cols, double *labels, char kernel[], double lambda_val, int iterations)
{
    // Create array and allocate memory for alphas
    double *alphas = (double *)calloc(rows, sizeof(double));
    double beta = 0;

    for (int t = 1; t < iterations + 1; t++)
    {
        for (int i = 0; i < rows; i++)
        {
            double eta = 1.0 / (lambda_val * t);

            double decision = 0;

            for (int j = 0; j < rows; j++)
            {
                decision += alphas[j] * labels[j] * RBFKernel(data[j], data[i], cols) + beta;
            }

            // Change alphas and betas
            if (labels[i] * decision < 1)
            {
                alphas[i] += eta * (labels[i] - lambda_val * alphas[i]);
                beta += eta * labels[i];
            }
        }
    }
    // Fill resultSVM
    resultSVM result;
    result.alphas = alphas;
    result.beta = beta;

    return result;
};

int main()
{
    // Initialization of parameters
    char kernel[] = "rbf";
    double lambda_val = 0.01;
    int iterations = 100;

    // Initialization of data
    int rows = 4, cols = 2;
    double **data = allocateMatrix(rows, cols);

    // Fill data
    double dt[] = {1, 2, 2, 3, 3, 1, 4, 1};

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            data[i][j] = dt[i * cols + j];
        };
    };

    // Print data
    printf("Matrix data with %d rows and %d cols.\n", rows, cols);
    printMatrix(data, rows, cols, 1);

    // Init labels
    int init_labels[] = {1, 1, -1, -1};
    double *labels = (double *)malloc(rows * sizeof(double));

    for (int i = 0; i < rows; i++)
    {
        labels[i] = init_labels[i];
    }

    // Print labels
    printf("Vector y with size %d.\n", rows);
    printVector(labels, rows, 0);

    // SVM
    resultSVM result = pegasosKernelSVM(data, rows, cols, labels, kernel, lambda_val, iterations);
    printf("Vector alpha with size %d.\n", rows);
    printVector(result.alphas, rows, 3);
    printf("Beta: %d.\n", result.beta);

    return 0;
}