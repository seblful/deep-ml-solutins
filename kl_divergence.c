#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "utils.h"

double square(x)
{
    return x * x;
}

double calculateKLDivergence(double pMu, double pSigma, double qMu, double qSigma)
{
    ;
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
    return 0;
}