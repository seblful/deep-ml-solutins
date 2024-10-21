#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "utils.h"

typedef struct convResult
{
    double **data;
    size_t size;
} convResult;

double **padMatrix(double **X, size_t xSize, int padding, size_t padSize)
{

    // Allocate memory for padX;
    double **padX = (double **)malloc(padSize * sizeof(double *));
    for (int i = 0; i < padSize; i++)
    {
        padX[i] = (double *)calloc(padSize, sizeof(double));
    }

    // Fill zero matrix with original matrix
    for (int i = 0; i < xSize; i++)
    {
        for (int j = 0; j < xSize; j++)
        {
            padX[i + padding][j + padding] = X[i][j];
        }
    }

    return padX;
}

convResult performConvolution(double **X, size_t xSize, double **K, size_t kSize, int padding, int stride)
{
    // Pad image
    double **padX;
    size_t padSize;

    if (padding > 0)
    {
        padSize = xSize + padding * 2;
        padX = padMatrix(X, xSize, padding, padSize);
    }
    else
    {
        padSize = xSize;
        padX = X;
    }

    printMatrix(padX, padSize, padSize, 0);
    printf("%d\n", padSize);

    // Perform convolution
    size_t convSize = ((xSize - kSize + 2 * padding) / stride) + 1;

    double **convX = allocateMatrix(convSize, convSize);

    for (int i = 0; i < convSize; i++)
    {
        for (int j = 0; j < convSize; j++)
        {
            double sum = 0;
            for (int ki = 0; ki < kSize; ki++)
            {
                for (int kj = 0; kj < kSize; kj++)
                {
                    int pi = i * stride + ki;
                    int pj = j * stride + kj;
                    sum += padX[pi][pj] * K[ki][kj];
                }
            }
            convX[i][j] = sum;
        }
    }

    // Fill result
    convResult result;
    result.data = convX;
    result.size = convSize;

    // Free memory
    if (padding > 0)
    {
        for (int i = 0; i < padSize; i++)
        {
            free(padX[i]);
        }
        free(padX);
    }

    return result;
}

int main()
{
    int padding = 0, stride = 1;

    // Init X
    size_t xSize = 5;
    double init_X[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25};
    double **X = allocateMatrix(xSize, xSize);
    for (int i = 0; i < xSize; i++)
    {
        for (int j = 0; j < xSize; j++)
        {
            X[i][j] = init_X[i * xSize + j];
        }
    }

    printf("Matrix X with %zu rows and %zu cols.\n", xSize, xSize);
    printMatrix(X, xSize, xSize, 0);

    // Init kernel
    size_t kSize = 2;
    double init_K[] = {1, 2, 3, -1};
    double **K = allocateMatrix(kSize, kSize);
    for (int i = 0; i < kSize; i++)
    {
        for (int j = 0; j < kSize; j++)
        {
            K[i][j] = init_K[i * kSize + j];
        }
    }

    printf("Matrix K with %zu rows and %zu cols.\n", kSize, kSize);
    printMatrix(K, kSize, kSize, 1);

    // Perform convolution
    convResult result = performConvolution(X, xSize, K, kSize, padding, stride);
    printMatrix(result.data, result.size, result.size, 1);

    // Free memory
    freeMatrix(X, xSize);
    freeMatrix(K, kSize);
    freeMatrix(result.data, result.size);

    return 0;
}