#include <stdlib.h>
#include <stdio.h>

#include "utils.h"

double calculateMean(double *v, int size)
{
    // Declare sum
    double sum = 0;

    // Iterating through vector and calculate mean
    for (int i = 0; i < size; i++)
    {
        sum += v[i];
    }

    return sum / size;
};

double **createCovarianceMatrix(double **m, int f, int r)
{
    // Init arrays
    double *means = malloc(sizeof(double) * f);

    // Init result matrix
    double **result = (double **)malloc(sizeof(double *) * f);
    for (int i = 0; i < f; i++)
    {
        result[i] = (double *)calloc(sizeof(double), f);
    };

    // Calculate means
    for (int i = 0; i < f; i++)
    {
        means[i] = calculateMean(m[i], r);
    };

    // Fill matrix

    for (int i = 0; i < f; i++)
    {
        for (int j = 0; j < f; j++)
        {
            double sum = 0;
            for (int k = 0; k < r; k++)
            {
                sum += (m[i][k] - means[i]) * (m[j][k] - means[j]);
            }
            result[i][j] = sum / (r - 1);
        }
    };

    // Free memory
    free(means);

    return result;
};

double **performPCA(double **data, int rows, int cols)
{
    // Init covariance matrix;
    double **covMatrix = createCovarianceMatrix(data, rows, cols);
    printf("Covariance matrix covMatrix with %d rows and %d cols.\n", cols, cols);
    printMatrix(covMatrix, cols, cols, 1);
}

int main()
{
    // Number of principal of components
    int k = 1;

    // Initialization of data
    int rows = 3, cols = 2;
    double **data = allocateMatrix(rows, cols);

    // Fill data
    double dt[6] = {1, 2, 3, 4, 5, 6};
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

    // Perform PCA
    double **result = performPCA(data, rows, cols);
};
