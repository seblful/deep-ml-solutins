#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    double diff;

    // Find norm of vector through difference between vectors
    double norm = 0;
    for (int i = 0; i < n; i++)
    {
        diff = x[i] - y[i];
        norm += square(diff);
    }

    norm = sqrt(norm);

    double result = exp(-square(norm) / (2 * (square(sigma))));

    return result;
};

resultSVM pegasosKernelSVM(double **data, int rows, int cols, double *labels, char kernelType[], double lambda_val, int iterations)
{
    // Create array and allocate memory for alphas
    double *alphas = (double *)calloc(rows, sizeof(double));
    double beta = 0;

    double kernel;

    resultSVM result = {NULL, 0};

    for (int t = 1; t < iterations + 1; t++)
    {
        for (int i = 0; i < rows; i++)
        {
            double eta = 1.0 / (lambda_val * t);

            double decision = 0;

            for (int j = 0; j < rows; j++)
            {
                if (strcmp(kernelType, "linear") == 0)
                {

                    kernel = linearKernel(data[j], data[i], cols);
                }
                else if (strcmp(kernelType, "rbf") == 0)
                {
                    kernel = RBFKernel(data[j], data[i], cols);
                }
                else
                {
                    printf("Unknown kernel type\n");
                    return result;
                }
                decision += alphas[j] * labels[j] * kernel;
            }

            decision += beta;

            // Change alphas and betas
            if (labels[i] * decision < 1)
            {
                alphas[i] += eta * (labels[i] - lambda_val * alphas[i]);
                beta += eta * labels[i];
            }
        }
    }
    // Fill resultSVM
    result.alphas = alphas;
    result.beta = beta;

    return result;
};

int main()
{
    // Initialization of parameters
    char kernelType[] = "rbf";
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
    resultSVM result = pegasosKernelSVM(data, rows, cols, labels, kernelType, lambda_val, iterations);
    printf("Vector alpha with size %d.\n", rows);
    printVector(result.alphas, rows, 3);
    printf("Beta: %f.\n", result.beta);

    // Free memory
    freeMatrix(data, rows);
    free(labels);
    free(result.alphas);

    return 0;
}