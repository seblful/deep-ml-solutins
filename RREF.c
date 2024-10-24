#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

int main()
{
    // Init M
    size_t rows = 3, cols = 4;
    double init_M[] = {1, 2, -1, -4, 2, 3, -1, -11, -2, 0, -3, 22};
    double **M = allocateMatrix(rows, cols);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            M[i][j] = init_M[i * cols + j];
        }
    }

    printf("Matrix M with %zu rows and %zu cols.\n", rows, cols);
    printMatrix(M, rows, cols, 0);

    // RREF
    rref(M, rows, cols);

    printf("Matrix RREF M with %zu rows and %zu cols.\n", rows, cols);
    printMatrix(M, rows, cols, 0);

    // Free memory
    freeMatrix(M, rows);

    return 0;
}