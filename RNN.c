#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

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
    double **Wx = allocateMatrix(cols, cols);
    double **Wh = allocateMatrix(cols, cols);
    double *h = (double *)calloc(rows, sizeof(double));
    double *b = (double *)malloc(cols * sizeof(double));

    Wx[0][0] = 0.5;
    Wh[0][0] = 0.8;
    h[0] = 0;
    b[0] = 0;

    printf("Matrix Wx with %zu rows and %zu cols.\n", cols, cols);
    printMatrix(Wx, cols, cols, 0);
    printf("Matrix Wh with %zu rows and %zu cols.\n", cols, cols);
    printMatrix(Wh, cols, cols, 0);

    printf("Vector h with size %d.\n", rows);
    printVector(h, rows, 0);
    printf("Vector b with size %d.\n", cols);
    printVector(b, cols, 0);

    return 0;
}