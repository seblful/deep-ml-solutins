#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "utils.h"

typedef struct subsetResult
{
    double **X;
    double *y;
} subsetResult;

void shuffle(int *array, int n)
{
    for (int i = n - 1; i > 0; i--)
    {
        int j = rand() % (i + 1); // Pick a random index from 0 to i
        // Swap array[i] with the element at random index
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

subsetResult subsetDataset(double **X, size_t rows, size_t cols, double *y, int nSubsets, bool replacememts)
{
    int *indexes = (int *)malloc(rows * sizeof(int));

    if (replacememts == false)
    {
        // Fill indexes with range
        for (int i = 0; i < rows; i++)
        {
            indexes[i] = i;
        }

        // Shuffle indexes
        shuffle(indexes, rows);
    }

    else
    {
        for (int i = 0; i < nSubsets; i++)
        {
            int a = rand() % rows;
            indexes[i] = rand() % rows;
        };
    }

    // Print random indexes
    printf("Vector indexes with size %d.\n", nSubsets);
    for (int i = 0; i < nSubsets; i++)
    {
        printf("%d ", indexes[i]);
    }
    printf("\n");

    // Allocate memory for X and y
    double **subsetX = (double **)malloc(nSubsets * sizeof(double *));
    double *subsetY;

    // Fill subsets
    for (int i = 0; i < nSubsets; i++)
    {
        subsetX[i] = X[indexes[i]];
        subsetY[i] = y[indexes[i]];
    }

    // Fill result
    subsetResult result;
    result.X = subsetX;
    result.y = subsetY;

    return result;
}

int main()
{
    int nSubsets = 3;
    bool replacements = false;

    // Set seed
    srand(2);

    // Init X
    size_t rows = 5,
           cols = 2;
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

    // Init y
    double init_y[] = {1, 2, 3, 4, 5};
    double *y = (double *)malloc(rows * sizeof(double));
    // Fill y
    for (int i = 0; i < rows; i++)
    {
        y[i] = init_y[i];
    };

    // Subset
    subsetResult result = subsetDataset(X, rows, cols, y, nSubsets, replacements);

    // Print result
    printf("Matrix subsetX with %d rows and %d cols.\n", nSubsets, cols);
    printMatrix(result.X, nSubsets, cols, 0);

    printf("Vector subsetY with size %d.\n", nSubsets);
    printVector(result.y, nSubsets, 0);

    // Free memory
    freeMatrix(X, rows);
    free(y);
    free(result.X);
}