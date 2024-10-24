#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

double **reshapeMatrix(double **matrix, size_t rows, size_t cols,
                       size_t newRows, size_t newCols)
{
    // Check if reshape is possible
    if (rows * cols != newRows * newCols)
    {
        printf("Error: Cannot reshape matrix. Element count mismatch.\n");
        return NULL;
    }

    // Allocate new matrix
    double **reshaped = allocateMatrix(newRows, newCols);

    // Copy elements
    for (size_t i = 0; i < rows * cols; i++)
    {
        size_t oldRow = i / cols;
        size_t oldCol = i % cols;
        size_t newRow = i / newCols;
        size_t newCol = i % newCols;

        reshaped[newRow][newCol] = matrix[oldRow][oldCol];
    }

    return reshaped;
}

int main()
{
    // Init X
    size_t rows = 2, cols = 4;

    double init_X[] = {1, 2, 3, 4, 5, 6, 7, 8};
    double **X = allocateMatrix(rows, cols);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            X[i][j] = init_X[i * cols + j];
        }
    }

    printf("Matrix X with %zu rows and %zu cols.\n", rows, cols);
    printMatrix(X, rows, cols, 0);

    // New shape
    size_t newRows = 4, newCols = 2;

    double **Xr = reshapeMatrix(X, rows, cols, newRows, newCols);
    printf("Matrix Xr with %zu rows and %zu cols.\n", newRows, newCols);
    printMatrix(Xr, newRows, newCols, 0);

    // Free memory
    freeMatrix(X, rows);
    freeMatrix(Xr, newRows);

    return 0;
}