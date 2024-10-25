#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

double **inverseMatrix(double **A, size_t rows, size_t cols)
{
    if (rows != 2 || cols != 2)
    {
        return NULL; // Only handle 2x2 matrices
    }

    double determinant = A[0][0] * A[1][1] - A[0][1] * A[1][0];

    if (determinant == 0)
    {
        printf("Matrix is singular and cannot be inverted.\n");
        return NULL;
    }

    double **A_I = allocateMatrix(rows, cols);

    // Calculate the inverse using the formula
    A_I[0][0] = A[1][1] / determinant;
    A_I[0][1] = -A[0][1] / determinant;
    A_I[1][0] = -A[1][0] / determinant;
    A_I[1][1] = A[0][0] / determinant;

    return A_I;
}

int main()
{
    // Init matrices
    size_t rows = 2, cols = 2;

    double init_A[] = {4, 7, 2, 6};

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

    double **A_I = inverseMatrix(A, rows, cols);
    printf("Matrix A_I with %zu rows and %zu cols.\n", rows, cols);
    printMatrix(A_I, rows, cols, 2);

    // Free memory
    freeMatrix(A, rows);
    freeMatrix(A_I, rows);

    return 0;
}