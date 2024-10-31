#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "utils.h"

double square(double x)
{
    return x * x;
}

double calculateKLDivergence(double pMu, double pSigma, double qMu, double qSigma)
{
    double div = log(qSigma / pSigma) + ((square(pSigma) + square(pMu - qMu)) / 2 * square(qSigma)) - 0.5;

    return div;
}

int main()
{
    // Init variables
    double pMu = 0.0;
    double pSigma = 1.0;
    double qMu = 1.0;
    double qSigma = 1.0;

    // Calculate KL divergence
    double div = calculateKLDivergence(pMu, pSigma, qMu, qSigma);

    printf("KL Divergence is %f.\n", div);

    return 0;
}