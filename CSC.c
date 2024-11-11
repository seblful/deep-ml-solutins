#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "utils.h"

typedef struct CSCResult
{
    size_t size;
    double *values;
    double *rowIds;
    double *colPointer;
} CSCResult;

CSCResult performCSC(double **A, size_t rows, size_t cols)
{
    // Allocate memory for arrays
    double *values = (double *)malloc(rows * cols * sizeof(double));
    double *rowIds = (double *)malloc(rows * cols * sizeof(double));
    double *colPointer = (double *)malloc((cols + 1) * sizeof(double));

    size_t size = 0;

    // Row pointer
    colPointer[0] = 0;
    double counter = 0;

    // Iterating through array
    for (int j = 0; j < cols; j++)
    {
        double rowCounter = 0;
        for (int i = 0; i < rows; i++)
        {
            if (A[i][j] != 0)
            {
                counter++;
                values[size] = A[i][j];
                rowIds[size] = i;
                size++;
            };
        }
        colPointer[j + 1] = counter;
    };

    // Resize arrays to actual size
    double *tempValues = realloc(values, size * sizeof(double));
    double *tempColIds = realloc(rowIds, size * sizeof(double));
    values = tempValues;
    rowIds = tempColIds;

    // Fill result
    CSCResult result = {size, values, rowIds, colPointer};

    return result;
}

int main()
{
    // Initialize dimensions
    size_t rows = 3, cols = 4;

    // Initialize input data A
    double init_A[] = {0, 0, 3, 0, 1, 0, 0, 4, 0, 2, 0, 0};

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
    CSCResult result = performCSC(A, rows, cols);
    printf("Size: %zu.\n", result.size);
    printf("Vector values with size %zu.\n", result.size);
    printVector(result.values, result.size, 0);
    printf("Vector rowIds with size %zu.\n", result.size);
    printVector(result.rowIds, result.size, 0);
    printf("Vector colPointer with size %zu.\n", cols + 1);
    printVector(result.colPointer, cols + 1, 0);

    // Free memory
    freeMatrix(A, rows);
    free(result.values);
    free(result.rowIds);
    free(result.colPointer);

    return 0;
}