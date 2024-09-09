#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

int main()
{
    // Number of folds
    int k = 5;

    // Initialization of data
    int rows = 5, cols = 2;
    double **data = allocateMatrix(rows, cols);

    // Fill data
    double dt[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            data[i][j] = dt[i * cols + j];
        };
    };

    // Print data
    printf("Matrix data with %d rows and %d cols.\n", rows, cols);
    printMatrix(data, rows, cols, 0);

    return 0;
}