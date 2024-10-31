#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "utils.h"

void RNNForward(double **X, size_t rows, size_t cols, double **Wx, double **Wh,
                double *h, double *b)
{
    double sum;
    double *temp_h = (double *)calloc(cols, sizeof(double));

    for (int t = 0; t < rows; t++)
    {
        // Calculate Wx * x_t
        for (int i = 0; i < cols; i++)
        {
            sum = 0;
            for (int j = 0; j < cols; j++)
            {
                sum += Wx[i][j] * X[t][j];
            }
            temp_h[i] = sum;
        }

        // Add Wh * h_t-1
        for (int i = 0; i < cols; i++)
        {
            sum = temp_h[i];
            for (int j = 0; j < cols; j++)
            {
                sum += Wh[i][j] * h[t * cols + j];
            }
            // Add bias and apply tanh
            h[(t + 1) * cols + i] = tanh(sum + b[i]);
        }
    }

    free(temp_h);
}

int main()
{
    // Initialize dimensions
    size_t rows = 3, cols = 1;

    // Initialize input data X
    double init_X[] = {1.0,
                       2.0,
                       3.0};

    double **X = allocateMatrix(rows, cols);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            X[i][j] = init_X[i * cols + j];
        }
    }

    // Initialize weight matrices
    double **Wx = allocateMatrix(cols, cols);
    double **Wh = allocateMatrix(cols, cols);

    // Example weights for Wx
    double init_Wx[] = {0.5};

    // Example weights for Wh
    double init_Wh[] = {
        0.8};

    for (int i = 0; i < cols; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            Wx[i][j] = init_Wx[i * cols + j];
            Wh[i][j] = init_Wh[i * cols + j];
        }
    }

    // Initialize hidden states (including initial state)
    double *h = (double *)calloc((rows + 1) * cols, sizeof(double));

    // Initialize biases
    double *b = (double *)calloc(cols, sizeof(double));
    b[0] = 0;

    // Print initial values
    printf("Input matrix X (%zux%zu):\n", rows, cols);
    printMatrix(X, rows, cols, 0);

    printf("\nWeight matrix Wx (%zux%zu):\n", cols, cols);
    printMatrix(Wx, cols, cols, 0);

    printf("\nWeight matrix Wh (%zux%zu):\n", cols, cols);
    printMatrix(Wh, cols, cols, 0);

    printf("\nInitial hidden states:\n");
    printVector(h, cols, 4);

    // Forward pass
    RNNForward(X, rows, cols, Wx, Wh, h, b);

    // Print final hidden state
    printf("\nFinal hidden state:\n");
    for (int i = 0; i < cols; i++)
    {
        printf("%.4f ", h[rows * cols + i]);
    }
    printf("\n");

    // Free memory
    freeMatrix(X, rows);
    freeMatrix(Wx, cols);
    freeMatrix(Wh, cols);
    free(h);
    free(b);

    return 0;
}