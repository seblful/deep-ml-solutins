#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

double *calculateJacobi(double **A, double *b, double *x, int rows, int cols, int n)
{
    // Temporary array for new values
    double *x_new = malloc(sizeof(double) * rows);

    for (int iter = 0; iter < n; iter++)
    {
        for (int i = 0; i < rows; i++)
        {
            double sigma = 0;
            for (int j = 0; j < rows; j++)
            {
                if (j != i)
                {
                    sigma += A[i][j] * x[j];
                }
            }
            x_new[i] = (1.0 / A[i][i]) * (b[i] - sigma);
        }

        // Update x with new values
        for (int i = 0; i < rows; i++)
        {
            x[i] = x_new[i];
        }
    }
    // Free the temporary array
    free(x_new);
    return x;
}
int main()
{
    // Declaration number of linear equations, number of unknown variables
    int rows = 3, cols = 3;

    // Init matrix
    double **A = (double **)malloc(sizeof(double *) * rows);
    for (int i = 0; i < rows; i++)
    {
        A[i] = (double *)malloc(sizeof(double) * cols);
    };

    // Fill matrix
    A[0][0] = 5;
    A[0][1] = -2;
    A[0][2] = 3;

    A[1][0] = -3;
    A[1][1] = 9;
    A[1][2] = 1;

    A[2][0] = 2;
    A[2][1] = -1;
    A[2][2] = -7;

    // Print matrix
    printf("Matrix with %d rows and %d cols.\n", rows, cols);
    printMatrix(A, rows, cols, 2);

    // Init b vector
    double *b = malloc(sizeof(double) * rows);

    // Fill vector
    b[0] = -1;
    b[1] = 2;
    b[2] = 3;

    // Print vector b
    printf("Vector with size %d.\n", rows);
    printVector(b, rows, 2);

    // Init x vector
    double *x = malloc(sizeof(double) * rows);
    // Fill vector
    x[0] = 0;
    x[1] = 0;
    x[2] = 0;

    // Print vector x
    printf("Vector with size %d.\n", rows);
    printVector(x, rows, 2);

    // Iterate with Jacobi method
    x = calculateJacobi(A, b, x, rows, cols, 2);

    // Print result vector x
    printf("Vector with size %d.\n", rows);
    printVector(x, rows, 4);

    // Free allocated memory
    for (int i = 0; i < rows; i++)
    {
        free(A[i]);
    }
    free(A);
    free(b);
    free(x);

    return 0;
};