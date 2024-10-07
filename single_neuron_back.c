#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "utils.h"

double sigmoid(double z)
{
    return 1 / (1 + exp(-z));
}

double sigmoidDer(double z)
{
    return sigmoid(z) * (1 - sigmoid(z));
}

double square(double x)
{
    return x * x;
}

double calculateDW(double **data, int rows, int cols, double *result, double *labels)
{

    double sum = 0;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; i < cols; i++)
        {
            sum += (sigmoid(result[i]) - labels[i]) * sigmoidDer(result[i]) * data[i][j];
        }
    }

    return sum * (2 / rows);
}

double calculateDb(double *result, double *labels, int n)
{
    double sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += (sigmoid(result[i]) - labels[i]) * sigmoidDer(result[i]);
    };

    return sum * (2 / n);
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
                  double bias,
                  double lr)
{
    double dW, db;

    dW = calculateDW(data, rows, cols, result, labels);
    printf("%f\n", dW);
    db = calculateDb(result, labels, rows);
    printf("%f\n", db);
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
    // Create array to store results
    double *result = (double *)malloc(rows * sizeof(double));

    for (int t = 0; t < epochs; t++)
    {
        forwardPass(data, rows, cols, weights, bias, result);
        backwardPass(data, rows, cols, result, labels, weights, bias, lr);
    };
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

    //    // Pass through single neuron
    double *result = singleNeuron(features, rows, cols, labels, weights, bias, lr, epochs);

    // // Print result
    // printf("Vector result with size %d.\n", rows);
    // printVector(result, rows, 4);

    return 0;
}
