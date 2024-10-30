#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

int performOSA(char source[], char target[])
{
    // Allocate zero matrix
    int sourceLen = strlen(source);
    int targetLen = strlen(target);

    int **OSAMatrix = (int **)malloc((sourceLen + 1) * sizeof(int *));
    for (int i = 0; i < (sourceLen + 1); i++)
    {
        OSAMatrix[i] = (int *)calloc((targetLen + 1), sizeof(int));
    }

    // Fill the first row and first column with index values
}

int main()
{
    char source[] = "butterfly";
    printf("Source is %s.\n", source);
    char target[] = "dragonfly";
    printf("Target is %s.\n", target);

    int distance = performOSA(source, target);
    printf("OSA distance is %d.\n", distance);

    return 0;
}