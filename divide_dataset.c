#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

typedef struct divideResult
{
    double **first;
    size_t firstRows;
    double **second;
    size_t secondRows;
} divideResult;

double findSplitRow(double **X, int rows, int cols, size_t iFeauture, int threshold)
{
    double nSplit;
    for (int i = 0; i < rows; i++)
    {
        if (X[i][iFeauture] == threshold)
        {
            nSplit = i;
            return nSplit;
        };
    }
    return 0;
}

double **createSplit(double **X, int subsetSize, int start, int end)
{
    // Allocate memory for subset
    double **subset = (double **)malloc(subsetSize * sizeof(double *));

    size_t index = 0;
    for (int i = start; i < end; i++)
    {
        subset[index] = X[i];
        index += 1;
    };

    return subset;
}

divideResult divideDataset(double **X, int rows, int cols, size_t iFeauture, int threshold)
{
    // Find number of row to split
    int nSplit = findSplitRow(X, rows, cols, iFeauture, threshold);

    // Split data
    double **first = createSplit(X, nSplit, 0, nSplit);
    double **second = createSplit(X, rows - nSplit, nSplit, rows);

    // Fill divideResult
    divideResult result;
    result.first = first;
    result.firstRows = nSplit;
    result.second = second;
    result.secondRows = rows - nSplit;

    return result;
}

void freeDivideResult(divideResult *result)
{
    if (result == NULL)
    {
        return;
    }

    // Free the first matrix
    if (result->first != NULL)
    {
        free(result->first);
        result->first = NULL;
    }

    // Free the second matrix
    if (result->second != NULL)
    {
        free(result->second);
        result->second = NULL;
    }

    // Reset the row counts
    result->firstRows = 0;
    result->secondRows = 0;
}

int main()
{
    // Init variavles
    size_t iFeauture = 0;
    int threshold = 5;

    // Init X
    size_t rows = 5, cols = 2;
    double init_X[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    double **X = allocateMatrix(rows, cols);
    // Fill x
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            X[i][j] = init_X[i * cols + j];
        };
    };

    printf("Matrix X with %d rows and %d cols.\n", rows, cols);
    printMatrix(X, rows, cols, 0);

    // Divide dataset
    divideResult result = divideDataset(X, rows, cols, iFeauture, threshold);

    // Print result
    printf("Matrix first with %d rows and %d cols.\n", result.firstRows, cols);
    printMatrix(result.first, result.firstRows, cols, 0);
    printf("Matrix second with %d rows and %d cols.\n", result.secondRows, cols);
    printMatrix(result.second, result.secondRows, cols, 0);

    // Free memory
    freeMatrix(X, rows);
    freeDivideResult(&result);
}