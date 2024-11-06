#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

double *orthogonalProjection(double *v, double *L, size_t size)
{
    double vL = vectorDotProduct(v, size, L, size);
    double LL = vectorDotProduct(L, size, L, size);
    double projScal = vL / LL;

    double *result = (double *)malloc(size * sizeof(double));
    scalarVectorMultiply(L, size, projScal, result);

    return result;
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
    printVector(result, size, 3);

    // Free memory
    free(v);
    free(L);
    free(result);

    return 0;
}