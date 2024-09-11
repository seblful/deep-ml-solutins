#include <stdio.h>
#include <stdlib.h>

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
    // Check for valid input
    if (f <= 0 || r <= 0)
    {
        fprintf(stderr, "Invalid dimensions for covariance matrix.\n");
        return NULL;
    }

    // Init arrays
    double *means = malloc(sizeof(double) * f);
    if (means == NULL)
    {
        fprintf(stderr, "Memory allocation failed for means.\n");
        return NULL;
    }

    // Init result matrix
    double **result = (double **)malloc(sizeof(double *) * f);
    if (result == NULL)
    {
        fprintf(stderr, "Memory allocation failed for result matrix.\n");
        free(means);
        return NULL;
    }
    for (int i = 0; i < f; i++)
    {
        result[i] = (double *)calloc(f, sizeof(double)); // Corrected calloc usage
        if (result[i] == NULL)
        {
            fprintf(stderr, "Memory allocation failed for result matrix row.\n");
            // Free previously allocated memory
            for (int j = 0; j < i; j++)
            {
                free(result[j]);
            }
            free(result);
            free(means);
            return NULL;
        }
    }

    // Calculate means for each feature
    for (int i = 0; i < f; i++)
    {
        means[i] = calculateMean(m[i], r);
    }

    // Fill covariance matrix
    for (int i = 0; i < f; i++)
    {
        for (int j = 0; j < f; j++)
        {
            double sum = 0;
            for (int k = 0; k < r; k++)
            {
                sum += (m[i][k] - means[i]) * (m[j][k] - means[j]);
            }
            result[i][j] = sum / (r - 1); // Sample covariance
        }
    }

    // Free memory for means
    free(means);

    return result;
}

int main()
{
    // Declaration number of feautures, number of records in each feautures
    int f = 3, r = 5;

    // Init matrix with vectors
    double **m = (double **)malloc(sizeof(double *) * f);
    for (int i = 0; i < f; i++)
    {
        m[i] = (double *)malloc(sizeof(double) * r);
    }

    // Fill matrix
    m[0][0] = 15;
    m[0][1] = 35;
    m[0][2] = 20;
    m[0][3] = 14;
    m[0][4] = 28;

    m[1][0] = 12.5;
    m[1][1] = 15.8;
    m[1][2] = 9.3;
    m[1][3] = 20.1;
    m[1][4] = 5.2;

    m[2][0] = 50;
    m[2][1] = 55;
    m[2][2] = 70;
    m[2][3] = 65;
    m[2][4] = 80;

    // Print matrix
    printf("Matrix with %d rows and %d cols.\n", f, r);
    printMatrix(m, f, r, 0);

    // Declare result matrix
    double **result;

    // Create covariance matrix from vectors
    result = createCovarianceMatrix(m, f, r);
    printf("Matrix with %d rows and %d cols.\n", f, f);
    printMatrix(result, f, f, 3);

    return 0;
};