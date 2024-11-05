#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "utils.h"

typedef struct CSRResult
{
    size_t size;
    double *values;
    double *colIds;
    double *rowPointer;
} CSRResult;

CSRResult performCSR(double **A, size_t rows, size_t cols)
{
    // Allocate memory for arrays
    double *values = (double *)malloc(rows * sizeof(double));
    double *colIds = (double *)malloc(rows * sizeof(double));
    double *rowPointer = (double *)malloc(rows * sizeof(double));

    size_t size = 0;

    // Row pointer
    rowPointer[0] = 0;
    int counterIdx = 1;
    double counter = 0;

    // Iterating through array
    for (int i = 0; i < rows; i++)
    {
        double rowCounter = 0;
        for (int j = 0; j < rows; j++)
        {
            if (A[i][j] != 0)
            {
                counter++;
                values[size] = A[i][j];
                colIds[size] = j;
                size++;
            };
        }
        rowPointer[counterIdx] = counter;
        counterIdx++;
    };

    CSRResult result = {size, values, colIds, rowPointer};

    return result;
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
    CSRResult result = performCSR(A, rows, cols);
    printf("Size: %zu.\n", result.size);
    printf("Vector values with size %zu.\n", result.size);
    printVector(result.values, result.size, 0);
    printf("Vector colIds with size %zu.\n", result.size);
    printVector(result.colIds, result.size, 0);
    printf("Vector rowPointer with size %zu.\n", result.size);
    printVector(result.rowPointer, result.size, 0);

    return 0;
}