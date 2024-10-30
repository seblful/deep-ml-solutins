#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "utils.h"

typedef struct QKVResult
{
    double **Q;
    double **K;
    double **V;
} QKVResult;

void softmax(double **matrix, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        double max_val = matrix[i][0];

        // Find maximum value in the row for numerical stability
        for (int j = 1; j < cols; j++)
        {
            if (matrix[i][j] > max_val)
            {
                max_val = matrix[i][j];
            }
        }

        double sum_exp = 0.0;

        // Calculate the sum of exponentials
        for (int j = 0; j < cols; j++)
        {
            sum_exp += exp(matrix[i][j] - max_val); // Subtract max_val for numerical stability
        }

        // Apply softmax to each element in the row
        for (int j = 0; j < cols; j++)
        {
            matrix[i][j] = exp(matrix[i][j] - max_val) / sum_exp;
        }
    }
}

QKVResult computeQKV(double **X, double **Wq, double **Wk, double **Wv, size_t size)
{
    // Allocate memory
    double **Q = allocateMatrix(size, size);
    double **K = allocateMatrix(size, size);
    double **V = allocateMatrix(size, size);

    // Multiplication
    matrixMultiply(X, size, size, Wq, size, size, Q);
    matrixMultiply(X, size, size, Wk, size, size, K);
    matrixMultiply(X, size, size, Wv, size, size, V);

    QKVResult result = {Q, K, V};

    return result;
}

double **selfAttention(double **X, double **Wq, double **Wk, double **Wv, size_t size)
{
    // Compute QKV
    QKVResult qkv = computeQKV(X, Wq, Wk, Wv, size);

    // Transpose K
    double **K_T = transposeMatrix(qkv.K, size, size);

    // Calculate attention
    double **QK_T = allocateMatrix(size, size);
    double **A = allocateMatrix(size, size);

    matrixMultiply(qkv.Q, size, size, K_T, size, size, QK_T);
    scalarMatrixDivision(QK_T, size, size, sqrt(size), QK_T);
    softmax(QK_T, size, size);
    matrixMultiply(QK_T, size, size, qkv.V, size, size, A);

    // Free memory
    freeMatrix(qkv.Q, size);
    freeMatrix(qkv.K, size);
    freeMatrix(qkv.V, size);
    freeMatrix(K_T, size);
    freeMatrix(QK_T, size);

    return A;
}

int main()
{
    // Init matrices
    size_t size = 2;
    double init_X[] = {1, 0, 0, 1};
    double init_Wq[] = {1, 0, 0, 1};
    double init_Wk[] = {1, 0, 0, 1};
    double init_Wv[] = {1, 2, 3, 4};
    double **X = allocateMatrix(size, size);
    double **Wq = allocateMatrix(size, size);
    double **Wk = allocateMatrix(size, size);
    double **Wv = allocateMatrix(size, size);

    // Fill matrices
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            X[i][j] = init_X[i * size + j];
            Wq[i][j] = init_Wq[i * size + j];
            Wk[i][j] = init_Wk[i * size + j];
            Wv[i][j] = init_Wv[i * size + j];
        };
    };

    printf("Matrix X with %d rows and %d cols.\n", size, size);
    printMatrix(X, size, size, 0);
    printf("Matrix Wq with %d rows and %d cols.\n", size, size);
    printMatrix(Wq, size, size, 0);
    printf("Matrix Wk with %d rows and %d cols.\n", size, size);
    printMatrix(Wk, size, size, 0);
    printf("Matrix Wv with %d rows and %d cols.\n", size, size);
    printMatrix(Wv, size, size, 0);

    double **A = selfAttention(X, Wq, Wk, Wv, size);
    printf("Matrix A with %d rows and %d cols.\n", size, size);
    printMatrix(A, size, size, 7);

    // Free memory
    freeMatrix(X, size);
    freeMatrix(Wq, size);
    freeMatrix(Wk, size);
    freeMatrix(Wv, size);
    freeMatrix(A, size);

    return 0;
}