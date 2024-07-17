#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "utils.h"

double *matrixVectorMul(double **m, double *v, int rows, int cols, int n)
{
    // Assert if wrong size of matrix or vector
    assert(cols == n); // Vector size n should be the same as number of matrix cols."

    // Init empty matrix
    double *result = calloc(sizeof(double), rows);

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            // Write code
            result[i] += m[i][j] * v[j];
        }
    }
    return result;
};

int main()
{
    // Declaration of rows, cols of matrix and size of vector
    int rows = 2, cols = 2, n = 2;

    // Init matrix
    double **m1 = (double **)malloc(rows * sizeof(double *));
    for (int i = 0; i < cols; i++)
    {
        m1[i] = (double *)malloc(cols * sizeof(double));
    };

    // Fill matrix
    m1[0][0] = 1;
    m1[0][1] = 2;
    m1[1][0] = 2;
    m1[1][1] = 4;

    printf("Matrix with %d rows and %d cols.\n", rows, cols);
    printMatrix(m1, rows, cols, 0);

    // Init vector
    double *v1 = (double *)malloc(n * sizeof(double));

    // Fill vector
    v1[0] = 1;
    v1[1] = 2;
    printf("Vector with size %d.\n", n);
    printVector(v1, n, 0);

    // Matrix vector multiplication
    // Init result matrix
    double *result;
    result = matrixVectorMul(m1, v1, rows, cols, n);
    printf("Matrix vector multiplication result is:\n");
    printVector(result, rows, 0);

    return 0;
}