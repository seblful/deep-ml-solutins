#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

double calculateDeterminant(double **M)
{
    return M[0][0] * M[1][1] - M[0][1] * M[1][0];
}

double **inverseMatrix(double **A, size_t rows, size_t cols)
{

    double determinant = calculateDeterminant(A);

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

double **transformMatrix(double **A, double **T, double **S, size_t rows, size_t cols)
{
    if (rows != 2 || cols != 2)
    {
        return NULL; // Only handle 2x2 matrices
    }
}

int main()
{
    // Init matrices
    size_t rows = 2, cols = 2;

    double init_A[] = {1, 2, 3, 4};
    double init_T[] = {2, 0, 0, 2};
    double init_S[] = {1, 1, 0, 1};
    double **A = allocateMatrix(rows, cols);
    double **T = allocateMatrix(rows, cols);
    double **S = allocateMatrix(rows, cols);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            A[i][j] = init_A[i * cols + j];
            T[i][j] = init_T[i * cols + j];
            S[i][j] = init_S[i * cols + j];
        }
    }

    printf("Matrix A with %zu rows and %zu cols.\n", rows, cols);
    printMatrix(A, rows, cols, 0);
    printf("Matrix T with %zu rows and %zu cols.\n", rows, cols);
    printMatrix(T, rows, cols, 0);
    printf("Matrix S with %zu rows and %zu cols.\n", rows, cols);
    printMatrix(S, rows, cols, 0);

    // Transform matrix
    double **transfMatrix = transformMatrix(A, T, S, rows, cols);
    printf("Matrix transfMatrix with %zu rows and %zu cols.\n", rows, cols);
    printMatrix(transfMatrix, rows, cols, 0);

    // Free memory
    freeMatrix(A, rows);
    freeMatrix(T, rows);
    freeMatrix(S, rows);
    freeMatrix(transfMatrix, rows);

    return 0;
}