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
    double length = sqrt(v[0] * v[0] + v[1] * v[1]);
    v[0] /= length;
    v[1] /= length;
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
    double **vectors = (double **)malloc(SIZE * sizeof(double *));

    // Calculate eigenvectors
    double v1[2] = {ATA[0][1], lambdas[0] - ATA[0][0]};
    double v2[2] = {ATA[0][1], lambdas[1] - ATA[0][0]};
    normalize(v1);
    normalize(v2);

    // Assign eigenvectors to matrix
    vectors[0] = v1;
    vectors[1] = v2;

    // Print
    printf("Matrix vectors with %d rows and %d cols.\n", SIZE, SIZE);
    printMatrix(vectors, SIZE, SIZE, SIZE);
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

    return 0;
}