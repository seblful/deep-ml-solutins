#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "utils.h"

void *RNNForward(double **X, size_t rows, size_t cols, double Wx, double Wh, double *h, double b)
{
    for (int i = 0; i < rows; i++)
    {
        h[i + 1] = tanh(Wx * X[i][0] + Wh * h[i] + b);
        printf("H %f.\n", h[i + 1]);
    }
}

int main()
{
    // Init X
    size_t rows = 3, cols = 1;

    double init_X[] = {1, 2, 3};
    double **X = allocateMatrix(rows, cols);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            X[i][j] = init_X[i * cols + j];
        }
    }

    printf("Matrix X with %zu rows and %zu cols.\n", rows, cols);
    printMatrix(X, rows, cols, 0);

    // Init Ws, h and b
    double Wx = 0.5;
    double Wh = 0.8;

    double *h = (double *)calloc(rows + 1, sizeof(double));

    double b = 0;

    printf("Wx is %f.\n", Wx);
    printf("Wh is %f.\n", Wh);
    printf("Vector h with size %d.\n", rows + 1);
    printVector(h, rows + 1, 0);
    printf("Bias is %0.2f.\n", b);

    RNNForward(X, rows, cols, Wx, Wh, h, b);

    printf("The final hidden state is approximately %f.\n", h[rows]);

    // Free memory
    freeMatrix(X, rows);

    return 0;
}