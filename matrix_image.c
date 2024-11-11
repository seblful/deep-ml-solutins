#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

typedef struct pivotResult
{
    double *data;
    size_t size;
} pivotResult;

void rref(double **M, size_t rows, size_t cols)
{
    size_t lead = 0;

    for (size_t r = 0; r < rows; r++)
    {
        if (lead >= cols)
            return;

        // Find the pivot row
        size_t i = r;
        while (M[i][lead] == 0)
        {
            i++;
            if (i == rows)
            {
                i = r;
                lead++;
                if (lead == cols)
                    return;
            }
        }

        // Swap the current row with the pivot row
        double *temp = M[r];
        M[r] = M[i];
        M[i] = temp;

        // Normalize the pivot row
        double divisor = M[r][lead];
        for (size_t j = 0; j < cols; j++)
        {
            M[r][j] /= divisor;
        }

        // Eliminate all other entries in this column
        for (size_t k = 0; k < rows; k++)
        {
            if (k != r)
            {
                double factor = M[k][lead];
                for (size_t j = 0; j < cols; j++)
                {
                    M[k][j] -= factor * M[r][j];
                }
            }
        }

        lead++;
    }
}

pivotResult findPivotColumns(double **M, int rows, int cols)
{
    double *pivotCols = (double *)malloc(cols * sizeof(double));
    size_t size = 0;

    for (int j = 0; j < cols; j++)
    {
        for (int i = 0; i < rows; i++)
        {
            if (M[i][j] == 1)
            { // Check for leading 1
                // Ensure all other entries in this column are zero
                int isPivotColumn = 1;
                for (int k = 0; k < rows; k++)
                {
                    if (k != i && M[k][j] != 0)
                    {
                        isPivotColumn = 0;
                        break;
                    }
                }
                if (isPivotColumn)
                {
                    pivotCols[size] = j;
                    size += 1;
                    break; // Move to the next column
                }
            }
        }
    }

    // Fill result
    pivotResult result = {pivotCols, size};

    return result;
}

double **matrixImage(double **M, size_t rows, size_t cols)
{
    // RREF
    rref(M, rows, cols);
    printf("Matrix RREF M with %zu rows and %zu cols.\n", rows, cols);
    printMatrix(M, rows, cols, 0);

    // Find pivot column
    pivotResult pivots = findPivotColumns(M, rows, cols);
    printf("Vector pivots with size %zu.\n", pivots.size);
    printVector(pivots.data, pivots.size, 0);
}

int main()
{
    // Init M
    size_t rows = 3, cols = 3;
    double init_M[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    double **M = allocateMatrix(rows, cols);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            M[i][j] = init_M[i * cols + j];
        }
    }

    printf("Matrix M with %zu rows and %zu cols.\n", rows, cols);
    printMatrix(M, rows, cols, 0);

    // Matrix Image
    matrixImage(M, rows, cols);

    // Free memory

    return 0;
}