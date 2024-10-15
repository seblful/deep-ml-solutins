#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

typedef struct BatchIterator
{
    double ***data;
    double **result;
    int numBatches;
    int batchSize;
    size_t rows;
    size_t cols;
} BatchIterator;

BatchIterator createBatchIterator(double **X, double *y, size_t rows, size_t cols, int batchSize)
{
    // Calculate number of batches
    int numBatches = (rows + batchSize - 1) / batchSize;
    double ***data = allocate3dMatrix(numBatches, batchSize, cols);
    double **result = allocateMatrix(numBatches, batchSize);

    // Fill data with batches from X
    for (int i = 0; i < numBatches; i++)
    {
        for (int j = 0; j < batchSize; j++)
        {
            int index = i * batchSize + j;
            if (index < rows)
            {
                data[i][j] = X[index];
                result[i][j] = y[index];
            }
            else
            {
                data[i][j] = NULL;
                result[i][j] = 0;
            }
        }
    }

    // Fill batch iterator
    BatchIterator batches;
    batches.data = data;
    batches.result = result;
    batches.numBatches = numBatches;
    batches.batchSize = batchSize;
    batches.rows = rows;
    batches.cols = cols;

    return batches;
}

void printBatches(BatchIterator batches)
{
    // Iterate through batches and print them
    for (int i = 0; i < (batches.rows + batches.batchSize - 1) / batches.batchSize; i++)
    {
        printf("Batch %d:\n", i);
        for (int j = 0; j < batches.batchSize; j++)
        {
            if (batches.data[i][j] != NULL)
            {
                printf("Row %d data: ", i * batches.batchSize + j);
                printMatrix(&batches.data[i][j], 1, batches.cols, 0);
                printf("Row %d result: %0.0f\n", i * batches.batchSize + j, batches.result[i][j]);
            }
        }
        printf("\n");
    };
}

void freeBatchIterator(BatchIterator *batches)
{
    if (batches == NULL)
    {
        return;
    }

    // Free the 3D data array
    if (batches->data != NULL)
    {
        for (int i = 0; i < batches->numBatches; i++)
        {
            if (batches->data[i] != NULL)
            {
                free(batches->data[i]);
            }
        }
        free(batches->data);
    }

    // Free the 2D result array
    if (batches->result != NULL)
    {
        for (int i = 0; i < batches->numBatches; i++)
        {
            if (batches->result[i] != NULL)
            {
                free(batches->result[i]);
            }
        }
        free(batches->result);
    }
}

int main()
{
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

    // Init y
    double init_y[] = {1, 2, 3, 4, 5};
    double *y = (double *)malloc(rows * sizeof(double));
    // Fill y
    for (int i = 0; i < rows; i++)
    {
        y[i] = init_y[i];
    };

    printf("Vector y with size %d.\n", rows);
    printVector(y, rows, 0);

    // Init batch size
    int batchSize = 2;

    // Create batches
    BatchIterator batches = createBatchIterator(X, y, rows, cols, batchSize);

    // Print batches
    printBatches(batches);

    // Free memory
    freeMatrix(X, rows);
    free(y);
    freeBatchIterator(&batches);

    return 0;
}