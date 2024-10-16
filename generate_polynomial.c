#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "utils.h"

int calcNumFeatures(int n_features, int degree)
{
    return (int)(tgamma(n_features + degree + 1) / (tgamma(n_features + 1) * tgamma(degree + 1)));
}

double **generatePolynom(double **X, int rows, int cols, int nFeatures, int degree)
{
    // Allocate memory for output
    double **output = allocateMatrix(rows, nFeatures);

    // Generate polynomial features
    for (int i = 0; i < rows; i++)
    {
        int idx = 0;

        // Add bias term (1)
        output[i][idx++] = 1.0;

        // Add original features
        for (int j = 0; j < cols; j++)
        {
            output[i][idx++] = X[i][j];
        }

        // Generate polynomial features
        for (int d = 2; d <= degree; d++)
        {
            for (int j = 0; j < cols; j++)
            {
                for (int k = j; k < cols; k++)
                {
                    output[i][idx++] = pow(X[i][j], d - (k - j)) * pow(X[i][k], k - j);
                }
            }
        }
    }
    return output;
}

int main()
{
    // Init variavles
    int degree = 0;

    // Init X
    size_t rows = 3, cols = 2;
    double init_X[] = {2, 3, 3, 4, 5, 6};
    double **X = allocateMatrix(rows, cols);

    // Fill X
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            X[i][j] = init_X[i * cols + j];
        };
    };

    printf("Matrix X with %d rows and %d cols.\n", rows, cols);
    printMatrix(X, rows, cols, 0);

    // Generate polynomial
    int nFeatures = calcNumFeatures(cols, degree);
    double **output = generatePolynom(X, rows, cols, nFeatures, degree);
    printf("Matrix output with %d rows and %d cols.\n", rows, nFeatures);
    printMatrix(output, rows, nFeatures, 0);

    // Free memory
    freeMatrix(X, rows);
    freeMatrix(output, rows);
}