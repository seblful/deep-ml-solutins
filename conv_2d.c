#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "utils.h"

typedef struct convResult
{
    double **data;
    size_t size;
} convResult;

double **padMatrix(double **X, size_t x_size, int padding, size_t padSize)
{

    // Allocate memory for padX;
    double **padX = (double **)malloc(padSize * sizeof(double *));
    for (int i = 0; i < padSize; i++)
    {
        padX[i] = (double *)calloc(padSize, sizeof(double));
    }

    // Fill zero matrix with original matrix
    for (int i = 0; i < x_size; i++)
    {
        for (int j = 0; j < x_size; j++)
        {
            padX[i + padding][j + padding] = X[i][j];
        }
    }

    return padX;
}

convResult performConvolution(double **X, size_t x_size, double **K, size_t k_size, int padding, int stride)
{
    // Pad image
    double **padX;
    size_t padSize;

    if (padding >= 0)
    {
        padSize = x_size + padding * 2;
        padX = padMatrix(X, x_size, padding, padSize);
    }
    else
    {
        padSize = x_size;
        padX = X;
    }

    printMatrix(padX, padSize, padSize, 0);
    printf("%d\n", padSize);
}

int main()
{
    int padding = 0, stride = 1;

    // Init X
    size_t x_size = 5;
    double init_X[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 18, 18, 19, 20, 21, 22, 23, 24, 25};
    double **X = allocateMatrix(x_size, x_size);
    for (int i = 0; i < x_size; i++)
    {
        for (int j = 0; j < x_size; j++)
        {
            X[i][j] = init_X[i * x_size + j];
        }
    }

    printf("Matrix X with %zu rows and %zu cols.\n", x_size, x_size);
    printMatrix(X, x_size, x_size, 0);

    // Init kernel
    size_t k_size = 2;
    double init_K[] = {1, 2, 3, -1};
    double **K = allocateMatrix(k_size, k_size);
    for (int i = 0; i < k_size; i++)
    {
        for (int j = 0; j < k_size; j++)
        {
            K[i][j] = init_K[i * k_size + j];
        }
    }

    printf("Matrix K with %zu rows and %zu cols.\n", k_size, k_size);
    printMatrix(K, k_size, k_size, 1);

    // Perform convolution
    convResult result = performConvolution(X, x_size, K, k_size, padding, stride);
}