#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

int main()
{
    double tx = 2, ty = 3;

    // Init points
    size_t rows = 3, cols = 2;
    double init_points[] = {0, 0, 1, 0, 0.5, 1};
    double **points = allocateMatrix(rows, cols);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            points[i][j] = init_points[i * cols + j];
        }
    }

    printf("Matrix points with %zu rows and %zu cols.\n", rows, cols);
    printMatrix(points, rows, cols, 1);

    return 0;
}