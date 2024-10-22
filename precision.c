#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

double calculatePrecision(double *yTrue, double *yPred, size_t size)
{
    double tpSum = 0;
    double fpSum = 0;

    for (int i = 0; i < size; i++)
    {
        if (yTrue[i] == 1 & yPred[i] == 1)
        {
            tpSum += 1;
        }
        else if (yTrue[i] == 0 & yPred[i] == 1)
        {
            fpSum += 1;
        }
    };

    return tpSum / (tpSum + fpSum);
}

int main()
{
    // Init x
    size_t size = 5;
    double init_y1[] = {1, 0, 1, 1, 0, 1};
    double init_y2[] = {1, 0, 1, 0, 0, 1};
    double *y1 = (double *)malloc(size * sizeof(double));
    double *y2 = (double *)malloc(size * sizeof(double));
    for (int i = 0; i < size; i++)
    {
        y1[i] = init_y1[i];
        y2[i] = init_y2[i];
    }

    printf("Vector y1 with size %zu.\n", size);
    printVector(y1, size, 0);
    printf("Vector y2 with size %zu.\n", size);
    printVector(y2, size, 0);

    // Calculate precision
    double precision = calculatePrecision(y1, y2, size);
    printf("Precision is %0.2f.\n", precision);

    return 0;
}