#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "utils.h"

typedef struct Set
{
    double *classes;
    size_t size;
} set_t;

bool isUnique(double *a, double x, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        if (a[i] == x)
        {
            return false;
        }
    }
    return true;
}

set_t createUniqueArray(double *y, size_t size)
{
    if (size == 0) // Added check for empty array
    {
        return (set_t){NULL, 0};
    }

    size_t setSize = 0;
    double *classes = (double *)malloc(size * sizeof(double));

    if (classes == NULL) // Added NULL check
    {
        return (set_t){NULL, 0};
    }

    classes[setSize++] = y[0];

    for (size_t i = 1; i < size; i++)
    {
        if (isUnique(classes, y[i], setSize))
        {
            classes[setSize++] = y[i];
        }
    }

    // Resize to actual size used
    double *temp = (double *)realloc(classes, setSize * sizeof(double));
    if (temp != NULL)
    {
        classes = temp;
    }

    return (set_t){classes, setSize};
}

double *calculateProbs(double *y, size_t ySize, double *classes, size_t classesSize)
{
    double *probs = (double *)malloc(classesSize * sizeof(double));

    for (int i = 0; i < classesSize; i++)
    {
        int count = 0;
        for (int j = 0; j < ySize; j++)
        {
            if (classes[i] == y[j])
            {
                count += 1;
            }
        }
        probs[i] = (double)count / (double)ySize;
    }

    return probs;
}

double giniImpurity(double *y, size_t size)
{
    // Find unique values
    set_t classesSet = createUniqueArray(y, size);
    // Calculate probabilities
    double *probs = calculateProbs(y, size, classesSet.classes, classesSet.size);

    // Calculate Gini Impurity
    double sum = 0;
    for (int i = 0; i < classesSet.size; i++)
    {
        sum += probs[i] * probs[i];
    }

    // Free memory
    free(classesSet.classes);
    free(probs);

    return 1 - sum;
}

int main()
{
    // Init y
    size_t size = 5;
    double init_y[] = {0, 1, 1, 1, 0};
    double *y = (double *)malloc(size * sizeof(double));
    for (int i = 0; i < size; i++)
    {
        y[i] = init_y[i];
    }

    printf("Vector y with size %zu.\n", size);
    printVector(y, size, 2);

    // Calculate Gini Impurity
    double impurity = giniImpurity(y, size);
    printf("Gini Umpurity is %0.3f.\n", impurity);

    // Free memory
    free(y);

    return 0;
}