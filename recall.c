#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

double calculateRecall(double *yTrue, double *yPred, size_t size)
{
    double tp = 0;
    double fn = 0;

    for (int i = 0; i < size; i++)
    {
        if (yTrue[i] == 1)
        {
            if (yPred[i] == 1)
            {
                tp += 1;
            }
            else if (yPred[i] == 0)
            {
                fn += 1;
            }
        }
    }

    return tp / (tp + fn);
}

int main()
{
    size_t size = 6;
    // Init yTrue
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
    double recall = calculateRecall(yTrue, yPred, size);
    printf("Recall of model's prediction is %.4f.\n", recall);

    // Free memory
    free(yTrue);
    free(yPred);
}