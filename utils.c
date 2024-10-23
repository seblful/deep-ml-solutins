#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

void printVector(double *v, int n, int precision)
{
    for (int i = 0; i < n; i++)
    {
        printf("%.*f ", precision, v[i]);
    }
    printf("\n");
};

void printUintVector(uint8_t *v, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%u ", v[i]);
    }
    printf("\n");
};

void printIntVector(int *v, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", v[i]);
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

void print3DMatrix(double ***m, int x, int y, int z, int precision)
{
    for (int i = 0; i < x; i++)
    {
        printf("\n");
        printMatrix(m[i], y, z, precision);
    }
    return;
};

void scalarVectorMultiply(double *v, size_t n, double value, double *result)
{
    for (int i = 0; i < n; i++)
    {
        result[i] = v[i] * value;
    }
}

void scalarVectorDivision(double *v, size_t n, double value, double *result)
{
    for (int i = 0; i < n; i++)
    {
        result[i] = v[i] / value;
    }
}

double vectorDotProduct(double *v1, size_t n1, double *v2, size_t n2)
{
    assert(n1 == n2); // Vector size n1 should be the same as vector size n2."

    double product = 0;
    for (int i = 0; i < n1; i++)
    {
        product += v1[i] * v2[i];
    }
    return product;
}

void matrixVectorMultiply(double **M, int rows, int cols, double *v, int n, double *result)
{
    // Assert if wrong size of matrix or vector
    assert(cols == n); // Vector size n should be the same as number of matrix cols."

    // Perform multiplication
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            // Write code
            result[i] += M[i][j] * v[j];
        }
    }
};

void matrixVectorDotProduct(double **M, size_t rows, size_t cols, double *v, int n, double *result)

{
    // Assert if wrong size of matrix or vector
    assert(cols == n); // Vector size n should be the same as number of matrix cols."

    for (int i = 0; i < rows; i++)
    {
        result[i] = 0;
        for (int j = 0; j < cols; j++)
        {
            result[i] += M[i][j] * v[j];
        }
    }
}

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

// Function to allocate a 3D array
double ***allocate3dMatrix(int x, int y, int z)
{
    double ***arr = malloc(x * sizeof(double **));
    for (int i = 0; i < x; i++)
    {
        arr[i] = allocateMatrix(y, z);
    }
    return arr;
}

// Function to free a 2D array
void freeMatrix(double **matrix, int rows)
{
    for (int i = 0; i < rows; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}

void free3dMatrix(double ***arr, int x, int y)
{
    for (int i = 0; i < x; i++)
    {
        freeMatrix(arr[i], y);
    };
}