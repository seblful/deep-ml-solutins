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

double calculateRecall(double *yTrue, double *yPred, size_t size)
{
    double tpSum = 0;
    double fnSum = 0;

    for (int i = 0; i < size; i++)
    {
        if (yTrue[i] == 1)
        {
            if (yPred[i] == 1)
            {
                tpSum += 1;
            }
            else if (yPred[i] == 0)
            {
                fnSum += 1;
            }
        }
    }

    return tpSum / (tpSum + fnSum);
}

double calculateFScore(double *yTrue, double *yPred, size_t size, double beta)
{
    double precision = calculatePrecision(yTrue, yPred, size);
    double recall = calculateRecall(yTrue, yPred, size);
    double fScore = (1 + beta * beta) * ((precision * recall) / ((beta * beta * precision) + recall));

    return fScore;
}
int main()
{
    double beta = 1.0;

    // Init yTrue
    size_t size = 6;
    double initYTrue[] = {1, 0, 1, 1, 0, 1};
    double initYPred[] = {1, 0, 1, 0, 0, 1};
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

    // Calculate recall
    double fScore = calculateFScore(yTrue, yPred, size, beta);
    printf("F-Score of model's prediction is %.3f.\n", fScore);

    // Free memory
    free(yTrue);
    free(yPred);

    return 0;
}