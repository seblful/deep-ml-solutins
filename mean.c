#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "utils.h"

double *calculateMean(double **X, size_t rows, size_t cols, char *mode)
{
    // Find Mode
    bool isRowsMode = strcmp(mode, "row") == 0;
    size_t first = isRowsMode ? rows : cols;
    size_t second = isRowsMode ? cols : rows;

    // Allocate memory
    double *mean = (double *)malloc(first * sizeof(double));

    for (int i = 0; i < first; i++)
    {
        double sum = 0;
        for (int j = 0; j < second; j++)
        {

            sum += isRowsMode ? X[i][j] : X[j][i];
        }
        mean[i] = sum / first;
    }

    return mean;
}

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