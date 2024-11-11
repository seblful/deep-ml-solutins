#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

typedef struct pivotResult
{
    int *data;
    size_t size;
} pivotResult;

typedef struct imageResult
{
    double **data;
    size_t rows;
    size_t cols;
} imageResult;

double **rref(double **M, size_t rows, size_t cols)
{
    // Make copy of original matrix
    double **rrefM = allocateMatrix(rows, cols);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            rrefM[i][j] = M[i][j];
        }
    }

    size_t lead = 0;

    for (size_t r = 0; r < rows; r++)
    {
        if (lead >= cols)
            return rrefM;

        // Find the pivot row
        size_t i = r;
        while (rrefM[i][lead] == 0)
        {
            i++;
            if (i == rows)
            {
                i = r;
                lead++;
                if (lead == cols)
                    return rrefM;
            }
        }

        // Swap the current row with the pivot row
        double *temp = rrefM[r];
        rrefM[r] = rrefM[i];
        rrefM[i] = temp;

        // Normalize the pivot row
        double divisor = rrefM[r][lead];
        for (size_t j = 0; j < cols; j++)
        {
            rrefM[r][j] /= divisor;
        }

        // Eliminate all other entries in this column
        for (size_t k = 0; k < rows; k++)
        {
            if (k != r)
            {
                double factor = rrefM[k][lead];
                for (size_t j = 0; j < cols; j++)
                {
                    rrefM[k][j] -= factor * rrefM[r][j];
                }
            }
        }

        lead++;
    }

    return rrefM;
}

pivotResult findPivotColumns(double **M, int rows, int cols)
{
    int *pivotCols = (int *)malloc(cols * sizeof(int));
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

imageResult matrixImage(double **M, size_t rows, size_t cols)
{
    // RREF
    double **rrefM = rref(M, rows, cols);
    printf("Matrix RREF M with %zu rows and %zu cols.\n", rows, cols);
    printMatrix(rrefM, rows, cols, 0);

    // Find pivot column
    pivotResult pivots = findPivotColumns(rrefM, rows, cols);
    printf("Vector pivots with size %zu.\n", pivots.size);
    printVector(pivots.data, pivots.size, 0);

    // Create image matrix
    double **imageM = allocateMatrix(rows, pivots.size);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < pivots.size; j++)
        {
            imageM[i][j] = M[i][pivots.data[j]];
        }
    }

    // Fill result
    imageResult result = {imageM, rows, pivots.size};

    // Free memory
    freeMatrix(rrefM, rows);
    free(pivots.data);

    return result;
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
    imageResult result = matrixImage(M, rows, cols);
    printf("Matrix imageM with %zu rows and %zu cols.\n", result.rows, result.cols);
    printMatrix(result.data, result.rows, result.cols, 0);

    // Free memory
    freeMatrix(M, rows);
    freeMatrix(result.data, result.rows);

    return 0;
}