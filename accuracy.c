#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

double calculateAccuracy(double *yTrue, double *yPred, size_t size)
{
    // Find sum of right answers
    double sum = 0;
    for (int i = 0; i < size; i++)
    {
        if (yTrue[i] == yPred[i])
        {
            sum += 1;
        };
    }

    return sum / size;
}
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

    // Calculate accuracy
    double accuracy = calculateAccuracy(yTrue, yPred, size);
    printf("Accuracy of model's prediction is %.4f.\n", accuracy);

    // Free memory
    free(yTrue);
    free(yPred);
}