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
    int rows, cols, n;

    // Init matrix
    int m1[2][2] = {{1, 2}, {2, 4}};
    rows = sizeof(m1) / sizeof(m1[0]);
    cols = sizeof(m1[0]) / sizeof(m1[0][0]);
    printf("Matrix with %d rows and %d cols.\n", rows, cols);

    // Init vector
    int v1[2] = {1, 2};
    n = sizeof(v1) / sizeof(v1[0]);
    printf("Vector with size %d.\n", n);

    // Matrix vector multiplication
    // Init matrix
    int *result;
    result = matrixVectorMul(**m1, *v1, rows, cols, n);
    printVector(result, rows);

    return 0;
}