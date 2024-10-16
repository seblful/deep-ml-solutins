#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

int main()

{
    size_t size = 5;

    // Init y
    double init_y[] = {1, 2, 3, 4, 5};
    double *y = (double *)malloc(size * sizeof(double));

    // Fill y
    for (int i = 0; i < size; i++)
    {
        y[i] = init_y[i];
    };

    // Print y
    printf("Vector y with size %d.\n", size);
    printVector(y, size, 0);
}