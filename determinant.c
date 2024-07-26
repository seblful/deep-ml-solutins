#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

void createMinor(double **A, double **minor, int rows, int cols, int skipRow, int skipCol)
{
    int minorRow = 0, minorCol = 0;

    for (int i = 0; i < rows; i++)
    {
        if (i == skipRow)
            continue;
        minorCol = 0;
        for (int j = 0; j < cols; j++)
        {
            if (j == skipCol)
                continue;
            minor[minorRow][minorCol] = A[i][j];
            minorCol++;
        }
        minorRow++;
    }
}

double calculateDeterminant(double **A, int rows, int cols)
{
    if (rows != cols)
    {
        printf("Error: Matrix must be square to calculate determinant.\n");
        return 0;
    }

    // Base case for 2x2 matrix
    if (rows == 2)
    {
        return A[0][0] * A[1][1] - A[0][1] * A[1][0];
    }

    double det = 0;
    int sign = 1;
    double **minor = allocateMatrix(rows - 1, cols - 1);

    for (int j = 0; j < cols; j++)
    {
        createMinor(A, minor, rows, cols, 0, j);

        // Print minor
        printf("\nMinor matrix for element A[0][%d]:\n", j);
        printMatrix(minor, rows - 1, cols - 1, 2);

        det += sign * A[0][j] * calculateDeterminant(minor, rows - 1, cols - 1);
        sign = -sign;
    }

    // Free the allocated memory for minor matrix
    for (int i = 0; i < rows - 1; i++)
    {
        free(minor[i]);
    }
    free(minor);

    return det;
}

int main()
{
    // Declaration of rows and cols in A matrix
    int rows = 4, cols = 4;

    // Declaration of determinant result
    double determinant;

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

    // Calculate dererminant
    determinant = calculateDeterminant(A, rows, cols);
    printf("Determinant of matrix is %f\n", determinant);

    return 0;
}