#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "utils.h"

double calculateDeterminant2x2(double **M)
{
    return M[0][0] * M[1][1] - M[1][0] * M[0][1];
}

double calculateDeterminant3x3(double **M)
{
    double det;

    det = M[0][0] * (M[1][1] * M[2][2] - M[1][2] * M[2][1]) -
          M[0][1] * (M[1][0] * M[2][2] - M[1][2] * M[2][0]) +
          M[0][2] * (M[1][0] * M[2][1] - M[1][1] * M[2][0]);

    return det;
}

double **createCofactorMatrix(double **M, int rows, int cols)
{
    // Allocate memory for matrices
    double **cofactorMatrix = allocateMatrix(rows, cols);
    double minorSize = 2;
    double **minorMatrix = allocateMatrix(minorSize, minorSize);

    // Calculate determinants of minor matrices
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            int row = 0, col = 0;

            for (int r = 0; r < 3; r++)
            {
                if (r == i)
                    continue;

                for (int c = 0; c < 3; c++)
                {
                    if (c == j)
                        continue;

                    minorMatrix[row][col] = M[r][c];
                    col++;
                }
                row++;
                col = 0;
            }

            // Apply the checkerboard pattern of signs
            if ((i + j) % 2 != 0)
            {
                cofactorMatrix[i][j] = -calculateDeterminant2x2(minorMatrix);
            }
            else
            {
                cofactorMatrix[i][j] = calculateDeterminant2x2(minorMatrix);
            }
        }
    }

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
    // Calculate determinant of original matrix
    double determinant = calculateDeterminant3x3(M);
    printf("Determinant: %f.\n", determinant);

    if (determinant == 0)
    {
        printf("Inverse of matrix does not exists when determinant is 0.\n");
    }

    // Allocate memory for matrices
    double **invMatrix = allocateMatrix(rows, cols);

    // Create cofactor and adjacent matrix
    double **cofMatrix = createCofactorMatrix(M, rows, cols);
    printf("Matrix cofMatrix with %d rows and %d cols.\n", rows, cols);
    printMatrix(cofMatrix, rows, cols, 2);

    double **adjMatrix = createAdjacentMatrix(cofMatrix, rows, cols);
    printf("Matrix adjMatrix with %d rows and %d cols.\n", rows, cols);
    printMatrix(adjMatrix, rows, cols, 2);

    // Apply the inverse
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            invMatrix[i][j] = adjMatrix[i][j] / determinant;
        }
    }

    printf("Matrix invMatrix with %d rows and %d cols.\n", rows, cols);
    printMatrix(invMatrix, rows, cols, 4);

    // Free memory
    freeMatrix(cofMatrix, rows);
    freeMatrix(adjMatrix, rows);

    return invMatrix;
};

double **transformMatrix(double **B, double **C, int rows, int cols)
{
    // Create inverse matrix of C
    double **invMatrix = createInverseMatrix(C, rows, cols);

    // Allocate memory for result matrix
    double **transfMatrix = allocateMatrix(rows, cols);

    // Multiply to basis B
    matrixMultiply(invMatrix, rows, cols, B, rows, cols, transfMatrix);

    // Free memory
    freeMatrix(invMatrix, rows);

    return transfMatrix;
}

int main()
{
    // Define rows and cols
    int rows = 3;
    int cols = 3;

    // Init matrices
    double init_B[] = {1, 0, 0, 0, 1, 0, 0, 0, 1};
    double init_C[] = {1, 2.3, 3, 4.4, 25, 6, 7.4, 8, 9};
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
    printf("Matrix transfMatrix with %d rows and %d cols.\n", rows, cols);
    printMatrix(transfMatrix, rows, cols, 4);

    // Free memory
    freeMatrix(B, rows);
    freeMatrix(C, rows);
    freeMatrix(transfMatrix, rows);

    return 0;
}