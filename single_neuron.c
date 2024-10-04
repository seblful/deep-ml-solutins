#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "utils.h"

int main()
{
    int rows = 3, cols = 2;

    // Init and fill matrix feautures
    double **features = allocateMatrix(rows, cols);
    double init_features[] = {0.5, 1.0, -1.5, -2.0, 2.0, 1.5};

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
    labels[0] = 0;
    labels[1] = 1;
    labels[2] = 0;

    printf("Vector labels with size %d.\n", rows);
    printVector(labels, rows, 0);

    // Init weights
    double *weights = (double *)malloc(cols * sizeof(double));
    weights[0] = 0.7;
    weights[1] = -0.4;

    printf("Vector weights with size %d.\n", cols);
    printVector(weights, cols, 1);

    // Init bias
    double bias = -0.1;

    return 0;
}