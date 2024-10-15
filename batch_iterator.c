#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

typedef struct BatchIterator
{
    double ***data;
    double **result;
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
    batches.batchSize = batchSize;
    batches.rows = rows;
    batches.cols = cols;

    return batches;
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

    return 0;
}