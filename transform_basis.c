#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "utils.h"

double calculateDeterminant(double **M)
{
    return M[0][0] * M[1][1] - M[0][1] * M[1][0];
}

double **createCofactorMatrix(double **M, int rows, int cols)
{
    // Allocate memory for matrices
    double **cofactorMatrix = allocateMatrix(rows, cols);
    double minorSize = 2;
    double **minorMatrix = allocateMatrix(minorSize, minorSize);

    // Calculate determinants of minor matrices
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            int minorRow = 0;
            for (int row = 0; row < rows; row++)
            {
                if (row == i)
                    continue; // Skip the current row
                int minorCol = 0;
                for (int col = 0; col < cols; col++)
                {
                    if (col == j)
                        continue; // Skip the current column
                    minorMatrix[minorRow][minorCol] = M[row][col];
                    minorCol++;
                }
                minorRow++;
            }

            cofactorMatrix[i][j] = calculateDeterminant(minorMatrix);
        };
    };

    // Free memory
    free(minorMatrix);

    return cofactorMatrix;
};

double **createAdjacentMatrix(double **cofMatrix, int rows, int cols)
{
    // Allocate memory for matrix
    double **adjMatrix = allocateMatrix(rows, cols);

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            adjMatrix[i][j] = cofMatrix[j][i];
        }
    };

    return adjMatrix;
};

double **createInverseMatrix(double **M, int rows, int cols)
{
    // Allocate memory for matrices
    double **invMatrix = allocateMatrix(rows, cols);

    // Create cofactor and adjacent matrix
    double **cofMatrix = createCofactorMatrix(M, rows, cols);
    printf("Matrix cofMatrix with %d rows and %d cols.\n", rows, cols);
    printMatrix(cofMatrix, rows, cols, 2);

    double **adjMatrix = createAdjacentMatrix(cofMatrix, rows, cols);
    printf("Matrix adjMatrix with %d rows and %d cols.\n", rows, cols);
    printMatrix(adjMatrix, rows, cols, 2);
};

double **transformMatrix(double **B, double **C, int rows, int cols)
{
    double **invMatrix = createInverseMatrix(C, rows, cols);
}

int main()
{
    // Define rows and cols
    int rows = 3;
    int cols = 3;

    // Init matrices
    double init_B[] = {1, 0, 0, 0, 1, 0, 0, 0, 1};
    // double init_C[] = {1, 2.3, 3, 4.4, 25, 6, 7.4, 8, 9};
    // double init_C[] = {1, 2, -1, 2, 1, 2, -1, 2, 1};

    double **B = allocateMatrix(rows, cols);
    double **C = allocateMatrix(rows, cols);

    // Fill matrices
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            B[i][j] = init_B[i * cols + j];
            C[i][j] = init_C[i * cols + j];
        };
    };

    // Print matrices
    printf("Matrix B with %d rows and %d cols.\n", rows, cols);
    printMatrix(B, rows, cols, 2);
    printf("Matrix C with %d rows and %d cols.\n", rows, cols);
    printMatrix(C, rows, cols, 2);

    // Transform matrix
    double **transfMatrix = transformMatrix(B, C, rows, cols);

    // Free memory
    freeMatrix(B, rows);
    freeMatrix(C, rows);

    return 0;
}