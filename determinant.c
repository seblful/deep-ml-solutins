#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

double calculateDeterminant(double **A, int rows, int cols)
{
    // Create minor matrix
    double **minor = allocateMatrix(rows - 1, cols - 1);

    // Iterating through matrix
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            ;
        }
    }
    return 0;
};

int main()
{
    // Declaration of rows and cols in A matrix
    int rows = 4, cols = 4;

    // Init matrix
    double **A;

    A = allocateMatrix(rows, cols);

    // Fill matrix
    double values[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            A[i][j] = values[i * cols + j];
        }
    };

    // Print matrix
    printf("Matrix A with %d rows and %d cols.\n", rows, cols);
    printMatrix(A, rows, cols, 0);

    return 0;
}