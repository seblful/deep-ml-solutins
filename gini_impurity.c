#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "utils.h"

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