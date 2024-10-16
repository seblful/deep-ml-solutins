#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

int main()
{
    size_t size = 6;
    // Init yTrue
    double initYTrue[] = {1, 0, 1, 1, 0, 1};
    double initYPred[] = {1, 0, 0, 1, 0, 1};
    double *yTrue = (double *)malloc(size * sizeof(double));
    double *yPred = (double *)malloc(size * sizeof(double));
    // Fill yTrue
    for (int i = 0; i < size; i++)
    {
        yTrue[i] = initYTrue[i];
        yPred[i] = initYPred[i];
    };

    printf("Vector yTrue with size %d.\n", size);
    printVector(yTrue, size, 0);

    printf("Vector yPred with size %d.\n", size);
    printVector(yPred, size, 0);
}