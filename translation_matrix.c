#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

#define SIZE 3

double **createTransMatrix(double tx, double ty)
{
    // Allocate memory for matrix
    double **transMatrix = allocateMatrix(SIZE, SIZE);

    // Fill matrix
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (i == j)
            {
                transMatrix[i][j] = 1;
            }
            else
            {
                transMatrix[i][j] = 0;
            }
        }
    }

    transMatrix[0][2] = tx;
    transMatrix[1][2] = ty;

    return transMatrix;
}

// Function to translate points using the translation matrix
double **translateMatrix(double **points, size_t rows, size_t cols, double tx, double ty)
{
    double **transMatrix = createTransMatrix(tx, ty);
    double **resultPoints = allocateMatrix(rows, cols); // Resulting points

    for (int i = 0; i < rows; i++)
    {
        double tempPoints[SIZE];
        tempPoints[0] = points[i][0];
        tempPoints[1] = points[i][1];
        tempPoints[2] = 1;

        double tempDot[SIZE];
        matrixVectorDotProduct(transMatrix, SIZE, SIZE, tempPoints, SIZE, tempDot);

        resultPoints[i][0] = tempDot[0]; // x'
        resultPoints[i][1] = tempDot[1]; // y'
    }

    // Free translation matrix memory
    freeMatrix(transMatrix, SIZE);

    return resultPoints;
}

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

    // Translate matrix
    double **result = translateMatrix(points, rows, cols, tx, ty);
    printf("Matrix result with %zu rows and %zu cols.\n", rows, cols);
    printMatrix(result, rows, cols, 2);

    // Free memory
    freeMatrix(points, rows);
    freeMatrix(result, rows);

    return 0;
}