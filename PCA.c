#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "utils.h"

// Function to compute the covariance matrix
double **createCovarianceMatrix(double **data, int rows, int cols)
{
    // Init result matrix
    double **result = allocateMatrix(rows, cols);

    for (int i = 0; i < cols; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            result[i][j] = 0.0;
            for (int k = 0; k < rows; k++)
            {
                result[i][j] += data[k][i] * data[k][j];
            }
            result[i][j] /= (rows - 1);
        }
    }

    return result;
}

// Function to standardize the dataset
void standardize(double **data, int rows, int cols)
{
    for (int j = 0; j < cols; j++)
    {
        double mean = 0.0;
        for (int i = 0; i < rows; i++)
        {
            mean += data[i][j];
        }
        mean /= rows;

        double std_dev = 0.0;
        for (int i = 0; i < rows; i++)
        {
            std_dev += (data[i][j] - mean) * (data[i][j] - mean);
        }
        std_dev = sqrt(std_dev / rows);

        for (int i = 0; i < rows; i++)
        {
            data[i][j] = (data[i][j] - mean) / std_dev;
        }
    }
}

// Function to find eigenvalues and eigenvectors
void powerIteration(double **matrix, double *eigenvector, int size, int max_iter)
{
    double *b_k = (double *)malloc(size * sizeof(double));
    for (int i = 0; i < size; i++)
    {
        b_k[i] = 1.0;
    }

    for (int iter = 0; iter < max_iter; iter++)
    {
        double *b_k1 = (double *)malloc(size * sizeof(double));
        for (int i = 0; i < size; i++)
        {
            b_k1[i] = 0.0;
            for (int j = 0; j < size; j++)
            {
                b_k1[i] += matrix[i][j] * b_k[j];
            }
        }

        double norm = 0.0;
        for (int i = 0; i < size; i++)
        {
            norm += b_k1[i] * b_k1[i];
        }
        norm = sqrt(norm);

        for (int i = 0; i < size; i++)
        {
            b_k[i] = b_k1[i] / norm;
        }

        free(b_k1);
    }

    for (int i = 0; i < size; i++)
    {
        eigenvector[i] = b_k[i];
    }

    free(b_k);
}

double **performPCA(double **data, int rows, int cols, int k)
{
    // Standardize data
    standardize(data, rows, cols);

    // Init covariance matrix;
    double **covMatrix = createCovarianceMatrix(data, rows, cols);
    printf("Matrix covMatrix with %d rows and %d cols.\n", cols, cols);
    printMatrix(covMatrix, cols, cols, 1);

    // Init principal components
    double **princComps = allocateMatrix(cols, k);

    // Find the eigenvalues and eigenvectors
    for (int i = 0; i < k; i++)
    {
        double *eigenvector = (double *)malloc(cols * sizeof(double));
        powerIteration(covMatrix, eigenvector, cols, 1000);

        for (int j = 0; j < cols; j++)
        {
            princComps[j][i] = eigenvector[j];
        }

        free(eigenvector);
    }

    // Free memory
    freeMatrix(covMatrix, cols);

    return princComps;
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
    double **princComps = performPCA(data, rows, cols, k);

    printf("Matrix princComps with %d rows and %d cols.\n", cols, k);
    printMatrix(princComps, cols, k, 4);
};
