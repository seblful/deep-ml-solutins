#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "utils.h"

// Function to calculate the mean of an array
double calculateMean(double *array, int n)
{
    double sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += array[i];
    }
    return sum / n;
}

// Function to calculate the correlation coefficient between two arrays
double calculateCorrelation(double *x, double *y, int n)
{
    double meanX = calculateMean(x, n);
    double meanY = calculateMean(y, n);

    double numerator = 0, denominatorX = 0, denominatorY = 0;

    for (int i = 0; i < n; i++)
    {
        double diffX = x[i] - meanX;
        double diffY = y[i] - meanY;
        numerator += diffX * diffY;
        denominatorX += diffX * diffX;
        denominatorY += diffY * diffY;
    }

    return numerator / sqrt(denominatorX * denominatorY);
}

// Function to calculate the correlation matrix
double **calculateCorrelationMatrix(double **X, int rows, int cols)
{
    double **corrMatrix = allocateMatrix(cols, cols);

    for (int i = 0; i < cols; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            double *col_i = (double *)malloc(rows * sizeof(double));
            double *col_j = (double *)malloc(rows * sizeof(double));

            for (int k = 0; k < rows; k++)
            {
                col_i[k] = X[k][i];
                col_j[k] = X[k][j];
            }

            corrMatrix[i][j] = calculateCorrelation(col_i, col_j, rows);

            free(col_i);
            free(col_j);
        }
    }

    return corrMatrix;
}

int main()
{
    // Init X
    size_t rows = 3, cols = 2;
    double init_X[] = {1, 2, 3, 4, 5, 6};
    double **X = allocateMatrix(rows, cols);
    // Fill x
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            X[i][j] = init_X[i * cols + j];
        };
    };

    printf("Matrix X with %d rows and %d cols.\n", rows, cols);
    printMatrix(X, rows, cols, 0);

    // Create correlation matrix
    double **corMatrix = calculateCorrelationMatrix(X, rows, cols);

    // Print matrix
    printf("Matrix corMatrix with %d rows and %d cols.\n", cols, cols);
    printMatrix(corMatrix, cols, cols, 2);

    // Free memory
    freeMatrix(X, rows);
    freeMatrix(corMatrix, cols);

    return 0;
}