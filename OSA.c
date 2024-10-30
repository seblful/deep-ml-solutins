#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

#define min(a, b) (((a) < (b)) ? (a) : (b))

int findMin(int a, int b, int c)
{
    int min = a;

    if (b < min)
    {
        min = b;
    }
    if (c < min)
    {
        min = c;
    }

    return min;
}

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
    for (int j = 1; j < targetLen + 1; j++)
    {
        OSAMatrix[0][j] = j;
    }

    for (int i = 1; i < sourceLen + 1; i++)
    {
        OSAMatrix[i][0] = i;
    }

    // Compute the OSA distance
    for (int i = 1; i < sourceLen + 1; i++)
    {
        for (int j = 1; j < targetLen + 1; j++)
        {
            int isNotEqual = source[i - 1] != target[j - 1] ? 1 : 0;
            // 1 if source[i - 1] != target[j - 1] else 0
            OSAMatrix[i][j] = findMin(
                OSAMatrix[i - 1, j] + 1,               // Deletion
                OSAMatrix[i][j - 1] + 1,               // Insertion
                OSAMatrix[i - 1][j - 1] + isNotEqual); // Substitution

            if (i > 1 & j > 1 & (source[i - 1] == target[j - 2]) & (source[i - 2] == target[j - 1]))
            {
                OSAMatrix[i][j] = min(OSAMatrix[i][j], OSAMatrix[i - 2][j - 2] + 1); // Transposition
            }
        }
    }

    // Print OSAMatrix
    printf("Matrix OSAMatrix with %zu rows and %zu cols.\n", sourceLen + 1, targetLen + 1);
    printIntMatrix(OSAMatrix, sourceLen + 1, targetLen + 1);

    // Retrieve distance
    int distance = OSAMatrix[sourceLen][targetLen];

    // Free memory
    freeMatrix(OSAMatrix, sourceLen + 1);

    return distance;
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