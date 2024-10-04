#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double sigmoid(double z)
{
    return 1 / (1 + exp(-z));
}

int main()
{
    double z = 0;
    double result = sigmoid(z);
    printf("Sigmoid of %0.3f is %0.3f.\n", z, result);
    return 0;
}