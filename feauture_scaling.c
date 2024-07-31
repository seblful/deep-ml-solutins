#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

double *calculateMean(double **data, int rows, int cols)
{

    // Allocate memory for mean
    double *mean = (double *)malloc(sizeof(double) * cols);

    // Iterate through data
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

double calculateSD() {};

double **standardizeData(double **data, int rows, int cols)
{
    // Calculate mean
    double *mean = calculateMean(data, rows, cols);
    printf("Vector mean with size %d.\n", cols);
    printVector(mean, cols, 4);
};

double **normalizeData(double **data) {};

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
    // Normalization
    norm_output = normalizeData(data);
}