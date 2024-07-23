#include <stdio.h>
#include <stdlib.h>

void printVector(double *v, int n, int precision)
{
    for (int i = 0; i < n; i++)
    {
        printf("%.*f ", precision, v[i]);
    }
    printf("\n");
};

void printMatrix(double **m, int rows, int cols, int precision)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("%.*f ", precision, m[i][j]);
        }
        printf("\n");
    }
    return;
};

void matrixMultiply(double **A, int rowsA, int colsA, double **B, int rowsB, int colsB, double **C)
{
    // Check if multiplication is possible
    if (colsA != rowsB)
    {
        printf("Matrix multiplication not possible: incompatible dimensions.\n");
        return;
    }

    // Initialize the result matrix C with zeros
    for (int i = 0; i < rowsA; i++)
    {
        for (int j = 0; j < colsB; j++)
        {
            C[i][j] = 0;
        }
    }

    // Perform multiplication
    for (int i = 0; i < rowsA; i++)
    {
        for (int j = 0; j < colsB; j++)
        {
            for (int k = 0; k < colsA; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

double **transposeMatrix(double **matrix, int rows, int cols)
{
    // Allocate memory for the transposed matrix
    double **transposedMatrix = (double **)malloc(cols * sizeof(double *));
    for (int i = 0; i < cols; i++)
    {
        transposedMatrix[i] = (double *)malloc(rows * sizeof(double));
    }

    // Transpose the matrix
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            transposedMatrix[j][i] = matrix[i][j];
        }
    }

    return transposedMatrix;
}

// Function to allocate a 2D array
double **allocateMatrix(int rows, int cols)
{
    double **matrix = (double **)malloc(rows * sizeof(double *));
    for (int i = 0; i < rows; i++)
    {
        matrix[i] = (double *)malloc(cols * sizeof(double));
    }
    return matrix;
}

// Function to free a 2D array
void freeMatrix(int **matrix, int rows)
{
    for (int i = 0; i < rows; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}