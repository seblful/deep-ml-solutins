#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "utils.h"

typedef struct CSRResult
{
    double *values;
    double colIds;
    double rowIds;
} CSRResult;

CSRResult performCSR(double **A, size_t rows, size_t cols)
{
    ;
}

int main()
{
    // Initialize dimensions
    size_t rows = 4, cols = 4;

    // Initialize input data A
    double init_A[] = {1, 0, 0, 0, 0, 2, 0, 0, 3, 0, 4, 0, 1, 0, 0, 5};

    double **A = allocateMatrix(rows, cols);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            A[i][j] = init_A[i * cols + j];
        }
    }

    printf("Matrix A with %zu rows and %zu cols.\n", rows, cols);
    printMatrix(A, rows, cols, 0);

    // Convert a Dense Matrix to Compressed Row Sparse (CSR) Format
    performCSR(A, rows, cols);

    return 0;
}