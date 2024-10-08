#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

int main()
{
    // Define rows and cols
    int rows = 3;
    int cols = 3;

    // Init matrices
    double init_B[] = {1, 0, 0, 0, 1, 0, 0, 0, 1};
    double init_C[] = {1, 2.3, 3, 4.4, 25, 6, 7.4, 8, 9};

    double **B = allocateMatrix(rows, cols);
    double **C = allocateMatrix(rows, cols);

    // Fill matrices
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            B[i][j] = init_B[i * cols + j];
            C[i][j] = init_C[i * cols + j];
        };
    };

    // Print matrices
    printf("Matrix B with %d rows and %d cols.\n", rows, cols);
    printMatrix(B, rows, cols, 2);
    printf("Matrix C with %d rows and %d cols.\n", rows, cols);
    printMatrix(C, rows, cols, 2);

    // Free memory
    freeMatrix(B, rows);
    freeMatrix(C, rows);

    return 0;
}