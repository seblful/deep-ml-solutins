#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "utils.h"

typedef struct
{
    double *eigenValues;
    double **eigenVectors;
} Eigen;

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

Eigen findEig(double **matrix, int size)
{
    // Allocate memory for eigenvalue vector and eigenvectors matrix
    double *eigenvalues = (double *)malloc(size * sizeof(double));
    double **eigenvectors = allocateMatrix(size, size);

    double a = matrix[0][0];
    double b = matrix[0][1];
    double c = matrix[1][0];
    double d = matrix[1][1];

    // Calculate the trace and determinant of the matrix
    double trace = a + d;
    double determinant = a * d - b * c;

    // Calculate the eigenvalues using the quadratic formula
    double discriminant = sqrt(trace * trace - 4 * determinant);
    eigenvalues[0] = (trace + discriminant) / 2;
    eigenvalues[1] = (trace - discriminant) / 2;

    // Print eigenvalues
    printf("Vector eigenvalues with size %d.\n", size);
    printVector(eigenvalues, size, 2);

    // Calculate the eigenvectors
    for (int i = 0; i < 2; i++)
    {
        double lambda = eigenvalues[i];
        if (b != 0)
        {
            eigenvectors[i][0] = lambda - d;
            eigenvectors[i][1] = b;
        }
        else if (c != 0)
        {
            eigenvectors[i][0] = c;
            eigenvectors[i][1] = lambda - a;
        }
        else
        {
            eigenvectors[i][0] = 1;
            eigenvectors[i][1] = 0;
        }
    }

    // Print eigenvectors
    printf("Matrix eigenvectors with %d rows and %d cols.\n", size, size);
    printMatrix(eigenvectors, size, size, 2);

    // Assign vectors and values to struct
    Eigen eigen;
    eigen.eigenValues = eigenvalues;
    eigen.eigenVectors = eigenvectors;

    return eigen;
}

double **performPCA(double **data, int rows, int cols)
{
    // Init covariance matrix;
    double **covMatrix = createCovarianceMatrix(data, rows, cols);
    printf("Covariance matrix covMatrix with %d rows and %d cols.\n", cols, cols);
    printMatrix(covMatrix, cols, cols, 1);

    // Init eigen struct and find eigenvectors and eigenvalues
    Eigen eigen = findEig(covMatrix, cols);
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
