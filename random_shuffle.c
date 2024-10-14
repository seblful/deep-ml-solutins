#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "utils.h"

void shuffle(double **X, double *y, size_t rows, size_t cols)
{
    if (rows > 1)
    {
        // Create temp variables
        double temp_y;
        double *temp_x = (double *)malloc(cols * sizeof(double));

        for (size_t i = 0; i < rows - 1; i++)
        {
            size_t j = i + rand() / (RAND_MAX / (rows - i) + 1);

            // Shuffle X
            temp_x = X[j];
            X[j] = X[i];
            X[i] = temp_x;

            // Shuffle y
            temp_y = y[j];
            y[j] = y[i];
            y[i] = temp_y;
        }

        // Free memory
        free(temp_x);
    }
}

int main()
{
    // Init X
    int rows = 4, cols = 2;
    double init_X[] = {1, 2, 3, 4, 5, 6, 7, 8};
    double **X = allocateMatrix(rows, cols);
    // Fill x
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            X[i][j] = init_X[i * cols + j];
        };
    };

    printf("Matrix X with %d rows and %d cols.\n", rows, cols);
    printMatrix(X, rows, cols, 0);

    // Init y
    double init_y[] = {1, 2, 3, 4};
    double *y = (double *)malloc(rows * sizeof(double));
    // Fill y
    for (int i = 0; i < rows; i++)
    {
        y[i] = init_y[i];
    };

    printf("Vector y with size %d.\n", rows);
    printVector(y, rows, 0);

    // Set seet
    srand(4);

    // Shuffle data
    shuffle(X, y, rows, cols);

    // Print results
    printf("Shuffled matrix X with %d rows and %d cols.\n", rows, cols);
    printMatrix(X, rows, cols, 0);

    printf("Shuffled vector y with size %d.\n", rows);
    printVector(y, rows, 0);

    return 0;
}