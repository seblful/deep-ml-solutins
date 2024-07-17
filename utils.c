#include <stdio.h>
#include <stdlib.h>

void printVector(double *v, int n, int precision)
{
    for (int i = 0; i < n; i++)
    {
        printf("%.*f ", precision, v[i]);
    }
    printf("\n");
};

void printMatrix(double **m, int rows, int cols, int precision)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("%.*f ", precision, m[i][j]);
        }
        printf("\n");
    }
    return;
};