#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

double **diagonalizeVector(double *array, size_t size)
{
    // Allocate memory for result matrix
    double **m = (double **)malloc(size * sizeof(double *));
    for (int i = 0; i < size; i++)
    {
        m[i] = (double *)calloc(size, sizeof(double));
    }

    // Fill matrix
    for (int i = 0; i < size; i++)
    {
        m[i][i] = array[i];
    }

    return m;
}

int main()
{
    size_t size = 3;
    // Init x
    double init_x[] = {1, 2, 3};
    double *x = (double *)malloc(size * sizeof(double));
    // Fill x
    for (int i = 0; i < size; i++)
    {
        x[i] = init_x[i];
    };

    printf("Vector x with size %d.\n", size);
    printVector(x, size, 0);

    // Diagonalize vector
    double **result = diagonalizeVector(x, size);

    // Print result
    printf("Matrix result with %d rows and %d cols.\n", size, size);
    printMatrix(result, size, size, 0);

    // Free memory
    free(x);
    freeMatrix(result, size);
}