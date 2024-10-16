#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
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
}