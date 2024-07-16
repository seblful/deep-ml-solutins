#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "utils.h"

int *matrixVectorMul(int **m, int *v, int rows, int cols, int n)
{
    // Assert if wrong size of matrix or vector
    assert(cols == n); // Vector size n should be the same as number of matrix cols."

    // Init empty matrix
    int *result = calloc(sizeof(int), rows);

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
    int **m1 = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < cols; i++)
    {
        m1[i] = (int *)malloc(cols * sizeof(int));
    };

    // Fill matrix
    m1[0][0] = 1;
    m1[0][1] = 2;
    m1[1][0] = 2;
    m1[1][1] = 4;

    printf("Matrix with %d rows and %d cols.\n", rows, cols);
    printMatrix(m1, rows, cols);

    // Init vector
    int *v1 = (int *)malloc(n * sizeof(int));

    // Fill vector
    v1[0] = 1;
    v1[1] = 2;
    printf("Vector with size %d.\n", n);
    printVector(v1, n);

    // Matrix vector multiplication
    // Init result matrix
    int *result;
    result = matrixVectorMul(m1, v1, rows, cols, n);
    printf("Matrix vector multiplication result is:\n");
    printVector(result, rows);

    return 0;
}