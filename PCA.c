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
}

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

Eigen findEig(double **matrix, int size)
{
    if (size != 2)
    {
        fprintf(stderr, "This function only supports 2x2 matrices.\n");
        exit(EXIT_FAILURE);
    }

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
    double discriminant = trace * trace - 4 * determinant;
    if (discriminant < 0)
    {
        fprintf(stderr, "The matrix has complex eigenvalues.\n");
        free(eigenvalues);
        freeMatrix(eigenvectors, size);
        exit(EXIT_FAILURE);
    }

    discriminant = sqrt(discriminant);
    eigenvalues[0] = (trace + discriminant) / 2;
    eigenvalues[1] = (trace - discriminant) / 2;

    // Print eigenvalues
    printf("Eigenvalues:\n");
    printf("%lf, %lf\n", eigenvalues[0], eigenvalues[1]);

    // Calculate the eigenvectors
    for (int i = 0; i < 2; i++)
    {
        double lambda = eigenvalues[i];
        if (b != 0 || c != 0)
        {
            eigenvectors[i][0] = b != 0 ? lambda - d : 1;  // Eigenvector calculation
            eigenvectors[i][1] = b != 0 ? -a : lambda - a; // Adjust based on lambda
        }
        else
        {
            eigenvectors[i][0] = 1; // Default eigenvector
            eigenvectors[i][1] = 0;
        }
    }

    // Print eigenvectors
    printf("Eigenvectors:\n");
    for (int i = 0; i < size; i++)
    {
        printf("%lf, %lf\n", eigenvectors[i][0], eigenvectors[i][1]);
    }

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