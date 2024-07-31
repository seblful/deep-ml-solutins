#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "utils.h"

double *calculateMean(double **data, int rows, int cols)
{

    // Allocate memory for mean
    double *mean = (double *)malloc(sizeof(double) * cols);

    // Initialize sum of values to 0
    for (int j = 0; j < cols; j++)
    {
        mean[j] = 0;
    }

    // Iterate through data and add values to mean vector
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            mean[j] += data[i][j];
        }
    }

    // Calculate mean
    for (int i = 0; i < cols; i++)
    {
        mean[i] = mean[i] / rows;
    }

    return mean;
};

double *calculateSD(double **data, int rows, int cols, double *mean)
{
    // Allocate memory for SD
    double *sd = (double *)malloc(sizeof(double) * cols);

    // Initialize sum of squares to 0
    for (int j = 0; j < cols; j++)
    {
        sd[j] = 0;
    }

    // Iterate through data and add pre-calculated values to sd vector
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            sd[j] += pow((data[i][j] - mean[j]), 2);
        }
    }

    // Calculate SD
    for (int i = 0; i < cols; i++)
    {
        sd[i] = sqrt(sd[i] / (rows - 1)); // It's a sample
    }

    return sd;
};

double *findMin(double **data, int rows, int cols)
{
    // Allocate memory for minValues
    double *minValues = (double *)malloc(sizeof(double) * cols);

    // Initialize sum of values to INFINITY
    for (int j = 0; j < cols; j++)
    {
        minValues[j] = INFINITY;
    }

    // Iterate through data and find min
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            minValues[j] = fmin(minValues[j], data[i][j]);
        }
    }

    return minValues;
};

double *findMax(double **data, int rows, int cols)
{ // Allocate memory for maxValues
    double *maxValues = (double *)malloc(sizeof(double) * cols);

    // Initialize sum of values to -INFINITY
    for (int j = 0; j < cols; j++)
    {
        maxValues[j] = -INFINITY;
    }

    // Iterate through data and find min
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            maxValues[j] = fmax(maxValues[j], data[i][j]);
        }
    }

    return maxValues;
};

double **standardizeData(double **data, int rows, int cols)
{
    // Calculate mean
    double *mean = calculateMean(data, rows, cols);
    printf("Vector mean with size %d.\n", cols);
    printVector(mean, cols, 4);

    // Calculate standart deviation
    double *sd = calculateSD(data, rows, cols, mean);
    printf("Vector sd with size %d.\n", cols);
    printVector(sd, cols, 4);

    // Allocate memory for output
    double **output = allocateMatrix(rows, cols);

    // Standardize
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            output[i][j] = (data[i][j] - mean[j]) / sd[j];
        }
    }

    return output;
};

double **normalizeData(double **data, int rows, int cols)
{
    // Calculate minValues
    double *minValues = findMin(data, rows, cols);
    printf("Vector minValues with size %d.\n", cols);
    printVector(minValues, cols, 4);

    // Calculate maxValues
    double *maxValues = findMax(data, rows, cols);
    printf("Vector maxValues with size %d.\n", cols);
    printVector(maxValues, cols, 4);
};

int main()
{
    // Declaration of rows and cols in data matrix
    int rows = 3, cols = 2;

    // Init data
    double **data = allocateMatrix(rows, cols);

    // Fill data
    data[0][0] = 1;
    data[0][1] = 2;
    data[1][0] = 3;
    data[1][1] = 4;
    data[2][0] = 5;
    data[2][1] = 6;

    // Print data
    printf("Matrix data with %d rows and %d cols.\n", rows, cols);
    printMatrix(data, rows, cols, 0);

    // Init output
    double **st_output, **norm_output;

    // Standatization
    st_output = standardizeData(data, rows, cols);
    printf("Matrix st_output with %d rows and %d cols.\n", rows, cols);
    printMatrix(st_output, rows, cols, 4);

    // Normalization
    norm_output = normalizeData(data, rows, cols);
}