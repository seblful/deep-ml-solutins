#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

#include "utils.h"

double calculateMax(double *a, size_t n)
{
    double maxValue = -DBL_MAX;

    for (int i = 0; i < n; i++)
    {
        if (a[i] > maxValue)
        {
            maxValue = a[i];
        }
    }

    return maxValue;
}

double *logSoftmax(double *a, size_t n)
{
    // Allocate memory for result matrix
    double *result = (double *)malloc(n * sizeof(double));

    // Find max value of array
    double maxValue = calculateMax(a, n);

    // Find sum of exponents
    double sum = 0;

    for (int i = 0; i < n; i++)
    {
        sum += exp(a[i] - maxValue);
    }

    // Calculate log softmax
    double logSum = log(sum);

    for (int i = 0; i < n; i++)
    {
        result[i] = a[i] - maxValue - logSum;
    }

    return result;
}

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

    // Find log softmax
    double *result = logSoftmax(a, size);

    printf("Vector result with size %zu.\n", size);
    printVector(result, size, 4);

    // Free memory
    free(a);
    free(result);

    return 0;
}