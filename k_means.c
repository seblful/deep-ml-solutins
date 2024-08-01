#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

int main()
{
    // Initialization of rows and cols in data matrix
    int rows = 6, cols = 2;

    // Initialization of number of clusters (k), number of iterations
    int k = 2;
    int n = 10;

    // Initialization of points
    double **points = allocateMatrix(rows, cols);

    // Fill points
    double pts[12] = {1, 2, 1, 4, 1, 0, 10, 2, 10, 4, 10, 0};

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            points[i][j] = pts[i * cols + j];
        }
    }

    // Print points
    printf("Matrix points with %d rows and %d cols.\n", rows, cols);
    printMatrix(points, rows, cols, 0);

    // Initialization of centroids
    double **centroids = allocateMatrix(k, 2);

    // Fill centroids
    double cts[12] = {1, 1, 10, 1};

    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            centroids[i][j] = cts[i * k + j];
        }
    }

    // Print centroids
    printf("Matrix centroids with %d rows and %d cols.\n", k, k);
    printMatrix(centroids, k, k, 0);

    return 0;
}