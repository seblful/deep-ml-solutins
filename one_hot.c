#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

typedef struct oneHotResult
{
    uint8_t **data;
    size_t rows;
    size_t cols;
} oneHotResult;

int findMax(int *array, size_t size)
{
    int maxValue = INT_MIN;
    for (int i = 0; i < size; i++)
    {
        if (array[i] > maxValue)
        {
            maxValue = array[i];
        };
    };

    return maxValue;
}

oneHotResult encodeOneHot(int *y, size_t size)
{
    // Find max value of array
    int maxValue = findMax(y, size);

    // Allocate memory for result matrix
    uint8_t **oneHot = (uint8_t **)calloc(size, sizeof(uint8_t *));
    for (int i = 0; i < size; i++)
    {
        oneHot[i] = (uint8_t *)calloc(maxValue + 1, sizeof(uint8_t));
    }

    // Fill one-hot matrix
    for (int i = 0; i < size; i++)
    {
        oneHot[i][y[i]] = 1;
    }

    // Fill result
    oneHotResult result;
    result.data = oneHot;
    result.rows = size;
    result.cols = maxValue + 1;

    return result;
}

int main()
{
    size_t size = 5;

    // Init y
    int init_y[] = {0, 1, 2, 1, 0};
    int *y = (int *)malloc(size * sizeof(int));

    // Fill y
    for (int i = 0; i < size; i++)
    {
        y[i] = init_y[i];
    };

    // Print y
    printf("Vector y with size %d.\n", size);
    for (int i = 0; i < size; i++)
    {
        printf("%d ", y[i]);
    }
    printf("\n");

    // One-Hot Encode
    oneHotResult result = encodeOneHot(y, size);

    // Print result
    for (int i = 0; i < result.rows; i++)
    {
        for (int j = 0; j < result.cols; j++)
        {
            printf("%u ", result.data[i][j]);
        }
        printf("\n");
    }

    // Free memory
    free(y);
    for (int i = 0; i < size; i++)
    {
        free(result.data[i]);
    }
    free(result.data);
}