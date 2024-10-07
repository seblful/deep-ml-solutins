#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "utils.h"

double square(double x)
{
    return x * x;
}

double sigmoid(double z)
{
    return 1 / (1 + exp(-z));
}

double sigmoidDer(double z)
{
    return sigmoid(z) * (1 - sigmoid(z));
}

double calculateMSE(double *result, double *labels, int n)
{
    double sum = 0;

    for (int i = 0; i < n; i++)
    {
        sum += square(result[i] - labels[i]);
    };

    return sum / (double)n;
}

double calculateDW(double **data, int rows, double *result, double *labels, int j)
{
    double sum = 0;

    for (int i = 0; i < rows; i++)
    {
        sum += (sigmoid(result[i]) - labels[i]) * (sigmoidDer(result[i]) * data[i][j]);
    }

    return sum * (2 / (double)rows);
}

double calculateDb(double *result, double *labels, int n)
{
    double sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += (sigmoid(result[i]) - labels[i]) * sigmoidDer(result[i]);
    };

    return sum * (2 / (double)n);
}

void forwardPass(double **data, int rows, int cols, double *weights, double bias, double *result)
{
    // Find probabilities
    for (int i = 0; i < rows; i++)
    {
        double z = 0;

        for (int j = 0; j < cols; j++)
        {
            z += data[i][j] * weights[j];
        };

        z += bias;

        result[i] = sigmoid(z);
    };
}

void backwardPass(double **data,
                  int rows,
                  int cols,
                  double *result,
                  double *labels,
                  double *weights,
                  double *bias,
                  double lr)
{
    // Calculate and update weights
    double dW, db;
    for (int j = 0; j < cols; j++)
    {
        dW = calculateDW(data, rows, result, labels, j);
        weights[j] = weights[j] - dW * lr;
    }

    // Calculate and update bias
    db = calculateDb(result, labels, rows);
    *bias = *bias - db * lr;
}

double *singleNeuron(double **data,
                     int rows,
                     int cols,
                     double *labels,
                     double *weights,
                     double bias,
                     double lr,
                     int epochs)
{
    // Create array to store results and mse
    double *result = (double *)malloc(rows * sizeof(double));
    double *MSE = (double *)malloc(epochs * sizeof(double));

    for (int t = 0; t < epochs; t++)
    {
        printf("%d/%d epochs.\n", t + 1, epochs);
        forwardPass(data, rows, cols, weights, bias, result);
        backwardPass(data, rows, cols, result, labels, weights, &bias, lr);
        MSE[t] = calculateMSE(result, labels, rows);
    };

    // Print results
    printf("Vector result with size %d.\n", rows);
    printVector(result, rows, 4);
    printf("Vector weights with size %d.\n", cols);
    printVector(weights, cols, 4);
    printf("Bias: %f.\n", bias);

    // Free memory
    free(result);

    return MSE;
}

int main()
{
    int rows = 3;
    int cols = 2;

    // Init and fill matrix feautures
    double **features = allocateMatrix(rows, cols);
    double init_features[] = {1.0, 2.0, 2.0, 1.0, -1.0, -2.0};

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            features[i][j] = init_features[i * cols + j];
        };
    };

    // Print matrix
    printf("Matrix features with %d rows and %d cols.\n", rows, cols);
    printMatrix(features, rows, cols, 1);

    // Init labels
    double *labels = (double *)malloc(rows * sizeof(double));
    labels[0] = 1;
    labels[1] = 0;
    labels[2] = 0;

    printf("Vector labels with size %d.\n", rows);
    printVector(labels, rows, 0);

    // Init weights
    double *weights = (double *)malloc(cols * sizeof(double));
    weights[0] = 0.1;
    weights[1] = -0.2;

    printf("Vector weights with size %d.\n", cols);
    printVector(weights, cols, 1);

    // Init other parameters
    double bias = 0.0;
    double lr = 0.1;
    int epochs = 2;

    // Pass through single neuron
    double *MSE = singleNeuron(features, rows, cols, labels, weights, bias, lr, epochs);

    // Print result
    printf("Vector MSE with size %d.\n", epochs);
    printVector(MSE, epochs, 4);

    // Free memory
    freeMatrix(features, rows);
    free(labels);
    free(weights);
    free(MSE);

    return 0;
}
