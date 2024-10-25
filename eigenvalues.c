#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "utils.h"

double *findEigenValues(double **X, size_t rows, size_t cols)
{
    if (rows != 2 || cols != 2)
    {
        return NULL; // Only works for 2x2 matrices
    }

    // Extract matrix elements
    double a = X[0][0];
    double b = X[0][1];
    double c = X[1][0];
    double d = X[1][1];

    // Calculate trace and determinant
    double trace = a + d;
    double determinant = a * d - b * c;

    // Calculate discriminant of the characteristic equation
    double discriminant = trace * trace - 4 * determinant;

    // Allocate memory for eigenvalues
    double *eigenValues = (double *)malloc(2 * sizeof(double));

    // Calculate eigenvalues using the quadratic formula
    if (discriminant >= 0)
    {
        eigenValues[0] = (trace + sqrt(discriminant)) / 2.0;
        eigenValues[1] = (trace - sqrt(discriminant)) / 2.0;
    }
    else
    {
        // Handle complex eigenvalues if needed (not covered here)
        eigenValues[0] = eigenValues[1] = trace / 2.0;
        printf("Complex eigenvalues not handled in this implementation.\n");
    }

    return eigenValues;
}

int main()
{
    // Init X
    size_t rows = 2, cols = 2;

    double init_X[] = {2, 1, 1, 2};
    double **X = allocateMatrix(rows, cols);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            X[i][j] = init_X[i * cols + j];
        }
    }

    printf("Matrix X with %zu rows and %zu cols.\n", rows, cols);
    printMatrix(X, rows, cols, 0);

    double *eigenValues = findEigenValues(X, rows, cols);

    printf("Vector eigenValues with size %zu.\n", rows);
    printVector(eigenValues, rows, 2);

    // Free memory
    freeMatrix(X, rows);
    free(eigenValues);

    return 0;
}