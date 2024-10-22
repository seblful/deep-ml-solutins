#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

double linearKernel(double *x1, double *x2, size_t size)
{
    double kernel = 0;
    for (int i = 0; i < size; i++)
    {
        kernel += x1[i] * x2[i];
    }

    return kernel;
}

int main()
{
    // Init x
    size_t size = 3;
    double init_x1[] = {1, 2, 3};
    double init_x2[] = {4, 5, 6};
    double *x1 = (double *)malloc(size * sizeof(double));
    double *x2 = (double *)malloc(size * sizeof(double));
    for (int i = 0; i < size; i++)
    {
        x1[i] = init_x1[i];
        x2[i] = init_x2[i];
    }

    printf("Vector x1 with size %zu.\n", size);
    printVector(x1, size, 1);
    printf("Vector x2 with size %zu.\n", size);
    printVector(x2, size, 1);

    // Linear Kernel
    double kernel = linearKernel(x1, x2, size);
    printf("Linear Kernel is %0.2f.\n", kernel);

    // Free memory
    free(x1);
    free(x2);

    return 0;
}