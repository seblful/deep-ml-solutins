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

double giniImpurity(double *y, size_t size)
{
    set_t classesSet = createUniqueArray(y, size);
    printf("SIZE CLASSES: %zu.\n", classesSet.size);
    printVector(classesSet.classes, classesSet.size, 3);
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

    return 0;
}