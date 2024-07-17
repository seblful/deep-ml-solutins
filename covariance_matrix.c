#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

double **createCovarianceMatrix(int f, int r)
{
    // Init result matrix
    double **result = (double **)malloc(sizeof(double *) * f);
    for (int i = 0; i < f; i++)
    {
        result[i] = (double *)calloc(sizeof(double), f);
    };
};

int main()
{
    // Declaration number of feautures, number of records in each feautures
    int f = 2, r = 3;

    // Init matrix with vectors
    double **m = (double **)malloc(sizeof(double *) * f);
    for (int i = 0; i < f; i++)
    {
        m[i] = (double *)malloc(sizeof(double) * r);
    }

    // Fill matrix
    m[0][0] = 1;
    m[0][1] = 2;
    m[0][2] = 3;
    m[1][0] = 4;
    m[1][1] = 5;
    m[1][2] = 6;

    // Declare result matrix
    double **result;

    // Create covariance matrix from vectors
    result = createCovarianceMatrix();
    printMatrix(result, f, f);

    return 0;
};