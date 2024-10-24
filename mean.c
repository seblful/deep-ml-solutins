#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "utils.h"

int main()
{
    // Init X
    size_t rows = 3, cols = 3;

    double init_X[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
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

    // Parameters
    char mode[] = "column";

    // Calculate mean
    double *mean = calculateMean(X, rows, cols, mode);

    printf("Vector mean with size %zu.\n", strcmp(mode, "column") == 0 ? cols : rows);
    printVector(mean, rows, 1);

    // Free memory
    freeMatrix(X, rows);
    free(mean);

    return 0;
}