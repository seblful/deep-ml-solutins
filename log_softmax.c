#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "utils.h"

int main()
{
    size_t size = 3;
    // Init a
    double init_a[] = {1, 2, 3};
    double *a = (double *)malloc(size * sizeof(double));
    for (int i = 0; i < size; i++)
    {
        a[i] = init_a[i];
    }

    printf("Vector a with size %zu.\n", size);
    printVector(a, size, 0);
    return 0;
}