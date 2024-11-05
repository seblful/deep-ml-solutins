#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "utils.h"

// Calculate dot product of two vectors
double dotProduct(double *a, double *b, size_t n)
{
    double sum = 0.0;
    for (size_t i = 0; i < n; i++)
    {
        sum += a[i] * b[i];
    }
    return sum;
}

// Calculate residual vector: r = b - Ax
void calculateResidual(double **A, double *b, double *x, double *r, size_t rows, size_t cols)
{
    double *Ax = (double *)malloc(rows * sizeof(double));
    matrixVectorDotProduct(A, rows, cols, x, cols, Ax);

    for (size_t i = 0; i < rows; i++)
    {
        r[i] = b[i] - Ax[i];
    }
    free(Ax);
}

// Calculate alpha = (r^T * r) / (p^T * A * p)
double calculateAlpha(double **A, double *r, double *p, size_t rows, size_t cols)
{
    double *Ap = (double *)malloc(rows * sizeof(double));
    matrixVectorDotProduct(A, rows, cols, p, cols, Ap);

    double numerator = dotProduct(r, r, rows);
    double denominator = dotProduct(p, Ap, rows);

    free(Ap);
    return numerator / denominator;
}

// Calculate beta = (r_{k+1}^T * r_{k+1}) / (r_k^T * r_k)
double calculateBeta(double *r, double *rNext, size_t rows)
{
    double numerator = dotProduct(rNext, rNext, rows);
    double denominator = dotProduct(r, r, rows);
    return numerator / denominator;
}

// Calculate vector norm
double vectorNorm(double *v, size_t n)
{
    return sqrt(dotProduct(v, v, n));
}

void conjugateGradient(double **A, size_t rows, size_t cols, double *b, int maxIter, double tol, double *result)
{
    double *r = (double *)malloc(rows * sizeof(double));
    double *p = (double *)malloc(rows * sizeof(double));
    double *rNext = (double *)malloc(rows * sizeof(double));
    double *Ap = (double *)malloc(rows * sizeof(double));

    // Initialize result vector to zeros
    for (size_t i = 0; i < rows; i++)
    {
        result[i] = 0.0;
    }

    // Calculate initial residual
    calculateResidual(A, b, result, r, rows, cols);

    // Initialize search direction
    for (size_t i = 0; i < rows; i++)
    {
        p[i] = r[i];
    }

    for (int iter = 0; iter < maxIter; iter++)
    {
        // Calculate step size alpha
        double alpha = calculateAlpha(A, r, p, rows, cols);

        // Update solution and residual
        for (size_t i = 0; i < rows; i++)
        {
            result[i] += alpha * p[i];
        }

        matrixVectorDotProduct(A, rows, cols, p, cols, Ap);
        for (size_t i = 0; i < rows; i++)
        {
            rNext[i] = r[i] - alpha * Ap[i];
        }

        // Calculate beta
        double beta = calculateBeta(r, rNext, rows);

        // Update search direction
        for (size_t i = 0; i < rows; i++)
        {
            p[i] = rNext[i] + beta * p[i];
            r[i] = rNext[i];
        }

        // Check convergence
        if (vectorNorm(r, rows) < tol)
        {
            break;
        }
    }

    // Free memory
    free(r);
    free(p);
    free(rNext);
    free(Ap);
}

int main()
{
    int n = 5;
    double tol = 1e-8;

    // Initialize dimensions
    size_t rows = 2, cols = 2;

    // Initialize input data A
    double init_A[] = {4, 1, 1, 3};

    double **A = allocateMatrix(rows, cols);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            A[i][j] = init_A[i * cols + j];
        }
    }

    printf("Matrix A with %zu rows and %zu cols.\n", rows, cols);
    printMatrix(A, rows, cols, 2);

    // Init b
    double init_b[] = {1, 2};
    double *b = (double *)malloc(cols * sizeof(double));
    for (int i = 0; i < cols; i++)
    {
        b[i] = init_b[i];
    }

    printf("Vector b with size %zu.\n", cols);
    printVector(b, cols, 2);

    // Gaussian elimination
    double *result = (double *)malloc(rows * sizeof(double));
    conjugateGradient(A, rows, cols, b, n, tol, result);

    printf("Vector result with size %zu.\n", cols);
    printVector(result, cols, 8);

    // Free memory
    freeMatrix(A, rows);
    free(b);
    free(result);

    return 0;
}