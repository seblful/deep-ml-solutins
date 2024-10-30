#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

typedef struct QKVResult
{
    double **Q;
    double **K;
    double **V;
} QKVResult;

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

double selfAttention(double **X, double **Wq, double **Wk, double **Wv, size_t size)
{
    // Compute QKV
    QKVResult qkv = computeQKV(X, Wq, Wk, Wv, size);
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

    double result = selfAttention(X, Wq, Wk, Wv, size);

    // Free memory

    return 0;
}