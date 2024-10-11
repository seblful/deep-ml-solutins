#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "utils.h"

#define SIZE 2

typedef struct SVDResult
{
    double **U;
    double **S;
    double **V;
} SVDResult;

void normalize(double *v)
{
    double sum = 0;
    for (int i = 0; i < SIZE; i++)
    {
        sum += v[i] * v[i];
    }

    double length = sqrt(sum);

    for (int i = 0; i < SIZE; i++)
    {
        v[i] /= length;
    }
}

double *calculateEigenValues(double **ATA)
{
    // Allocate memory for eigenvalues
    double *lambdas = (double *)malloc(SIZE * sizeof(double));

    // Compute eigenvalues
    double trace = ATA[0][0] + ATA[1][1];
    double det = ATA[0][0] * ATA[1][1] - ATA[0][1] * ATA[1][0];
    double discriminant = trace * trace - 4 * det;
    lambdas[0] = (trace + sqrt(discriminant)) / 2;
    lambdas[1] = (trace - sqrt(discriminant)) / 2;

    // Print
    printf("Vector lambdas with size %d.\n", SIZE);
    printVector(lambdas, SIZE, SIZE);

    return lambdas;
};

double **calculateEigenVectors(double **ATA, double *lambdas)
{
    // Allocate memory for eigenvectors
    double **vectors = allocateMatrix(SIZE, SIZE);

    // Calculate eigenvectors
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (j % 2 == 0)
            {
                vectors[i][j] = ATA[0][1];
            }
            else
            {
                vectors[i][j] = lambdas[i] - ATA[0][0];
            }
        }
        // Normalize vectors
        normalize(vectors[i]);
    }

    // Print
    printf("Matrix vectors with %d rows and %d cols.\n", SIZE, SIZE);
    printMatrix(vectors, SIZE, SIZE, SIZE);

    return vectors;
}

double **compute_U(double **A, double **V)
{
    double **U = allocateMatrix(SIZE, SIZE);
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {

            U[j][i] = (A[j][0] * V[i][0]) + (A[j][1] * V[i][1]);
        }
    }

    // Transpose and normalize
    double **TU = transposeMatrix(U, SIZE, SIZE);
    for (int i = 0; i < SIZE; i++)
    {
        normalize(TU[i]);
    };

    // Free memory
    freeMatrix(U, SIZE);

    return TU;
}

SVDResult decomposeMatrix(double **A, int rows, int cols)
{
    // Product of original and transpose matrix
    double **ATA = allocateMatrix(rows, cols);
    matrixMultiply(transposeMatrix(A, rows, cols), rows, cols, A, rows, cols, ATA);

    printf("Matrix ATA with %d rows and %d cols.\n", rows, cols);
    printMatrix(ATA, rows, cols, 4);

    // Calculate eigenvalues and eigenvectorss
    double *lambdas = calculateEigenValues(ATA);
    double **vectors = calculateEigenVectors(ATA, lambdas);

    // Allocate memory and declare
    double **S = allocateMatrix(SIZE, SIZE);
    double **V = (double **)malloc(SIZE * sizeof(double *));
    double **U;

    // Compute S
    for (int i = 0; i < SIZE; i++)
    {
        S[i][i] = sqrt(lambdas[i]);
    }

    // Compute V
    V = vectors;

    // Compute U
    U = compute_U(A, V);

    // Fill result
    SVDResult result;
    result.U = U;
    result.S = S;
    result.V = V;

    // Free memory
    freeMatrix(ATA, SIZE);
    free(lambdas);

    return result;
}

int main()
{
    // Init matrix
    double **A = allocateMatrix(SIZE, SIZE);

    A[0][0] = -10;
    A[0][1] = 8;
    A[1][0] = 10;
    A[1][1] = -1;

    printf("Matrix A with %d rows and %d cols.\n", SIZE, SIZE);
    printMatrix(A, SIZE, SIZE, 2);

    // Perform SVD
    SVDResult result = decomposeMatrix(A, SIZE, SIZE);

    // Print results
    printf("Matrix U with %d rows and %d cols.\n", SIZE, SIZE);
    printMatrix(result.U, SIZE, SIZE, 4);
    printf("Matrix S with %d rows and %d cols.\n", SIZE, SIZE);
    printMatrix(result.S, SIZE, SIZE, 4);
    printf("Matrix V with %d rows and %d cols.\n", SIZE, SIZE);
    printMatrix(result.V, SIZE, SIZE, 4);

    // Free memory
    freeMatrix(A, SIZE);
    freeMatrix(result.U, SIZE);
    freeMatrix(result.S, SIZE);
    freeMatrix(result.V, SIZE);

    return 0;
}