#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

#define SIZE 2

double square(double x)
{
    return x * x;
}

double objective(double x[SIZE])
{
    return square(x[0]) + square(x[1]);
}

void gradient(double x[SIZE], double xg[SIZE])
{

    xg[0] = 2 * x[0];
    xg[1] = 2 * x[1];
}

int main()
{
    // Parameters
    double lr = 0.001;
    double beta1 = 0.9;
    double beta2 = 0.999;
    double epsilon = 1e-8;
    int nIterations = 1000;

    // Init x
    double *x = (double *)malloc(SIZE * sizeof(double));
    x[0] = 1;
    x[1] = 1;

    printf("Vector x with size %zu.\n", SIZE);
    printVector(x, SIZE, 0);

    return 0;
}