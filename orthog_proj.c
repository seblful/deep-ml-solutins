#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "utils.h"

double *orthogonalProjection(double *v, double *L, size_t size)
{
    ;
}

int main()
{
    // Init vectors
    size_t size = 2;
    double init_v[] = {3, 4};
    double init_L[] = {1, 0};
    double *v = (double *)malloc(size * sizeof(double));
    double *L = (double *)malloc(size * sizeof(double));

    for (int i = 0; i < size; i++)
    {
        v[i] = init_v[i];
        L[i] = init_L[i];
    };

    printf("Vector v with size %d.\n", size);
    printVector(v, size, 0);
    printf("Vector L with size %d.\n", size);
    printVector(L, size, 0);

    double *result = orthogonalProjection(v, L, size);
    printf("Vector result with size %d.\n", size);
    printVector(result, size, 0);

    return 0;
}