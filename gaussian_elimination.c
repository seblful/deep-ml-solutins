#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "utils.h"

void partialPivoting(double **A, size_t rows, size_t row_num, size_t col_num)
{
    size_t max_row = row_num;
    double max_val = fabs(A[row_num][col_num]);

    for (size_t i = row_num; i < rows; i++)
    {
        double current_val = fabs(A[i][col_num]);
        if (current_val > max_val)
        {
            max_val = current_val;
            max_row = i;
        }
    }

    // Swap rows if necessary
    if (max_row != row_num)
    {
        double *temp = A[row_num];
        A[row_num] = A[max_row];
        A[max_row] = temp;
    }
}

void gaussianElimination(double **A, size_t rows, size_t cols, double *b, double *result)
{
    // Augment the matrix A with vector b
    for (size_t i = 0; i < rows; i++)
    {
        A[i] = realloc(A[i], (cols + 1) * sizeof(double));
        A[i][cols] = b[i]; // Add b as the last column
    }
}

int main()
{
    // Initialize dimensions
    size_t rows = 3, cols = 3;

    // Initialize input data A
    double init_A[] = {2, 8, 4, 2, 5, 1, 4, 10, -1};

    double **A = allocateMatrix(rows, cols);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            A[i][j] = init_A[i * cols + j];
        }
    }

    printf("Matrix A with %zu rows and %zu cols.\n", rows, cols);
    printMatrix(A, rows, cols, 2);

    // Init b
    double init_b[] = {2, 5, 1};
    double *b = (double *)malloc(cols * sizeof(double));
    for (int i = 0; i < cols; i++)
    {
        b[i] = init_b[i];
    }

    printf("Vector b with size %zu.\n", cols);
    printVector(b, cols, 2);

    // Gaussian elimination
    double *result = (double *)malloc(rows * sizeof(double));
    gaussianElimination(A, rows, cols, b, result);

    printf("Vector result with size %zu.\n", cols);
    printVector(result, cols, 2);

    return 0;
}