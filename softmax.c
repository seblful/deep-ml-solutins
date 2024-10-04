#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "utils.h"

double *softmax(double *inputs, int n)
{
    // Create array of results
    double *result = (double *)malloc(n * sizeof(double));

    double sum;

    // Find sum of exponents
    for (int i = 0; i < n; i++)
    {
        sum += exp(inputs[i]);
    };

    // Find probability of each number
    for (int i = 0; i < n; i++)
    {
        result[i] = exp(inputs[i]) / sum;
    }

    return result;
}

int main()
{
    int n = 3;

    // Init and fill scores
    double *scores = (double *)malloc(n * sizeof(double));

    scores[0] = 1;
    scores[1] = 2;
    scores[2] = 3;

    // Print vector
    printf("Vector scores with size %d.\n", n);
    printVector(scores, n, 1);

    // Softmax
    double *result = softmax(scores, n);
    printf("Vector result with size %d.\n", n);
    printVector(result, n, 4);

    // Free memory
    free(scores);
    free(result);

    return 0;
}