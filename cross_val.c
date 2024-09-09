#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "utils.h"

void shuffleRows(double **array, int rows, int cols)
{
    srand(time(NULL)); // Seed the random number generator

    for (int i = rows - 1; i > 0; i--)
    {
        int r = rand() % (i + 1);

        // Swap rows
        for (int j = 0; j < cols; j++)
        {
            int temp = array[i][j];
            array[i][j] = array[r][j];
            array[r][j] = temp;
        }
    }
}

void swapSubArrays(double **array, int cols, int a, int b)
{
    // Return if a and b are equal
    if (a == b)
    {
        return;
    };

    // Swap array
    for (int i = 0; i < cols; i++)
    {
        double temp = array[a][i];
        array[a][i] = array[b][i];
        array[b][i] = temp;
    };
};

void createCrossData(double **data, int rows, int cols, double ***crossData, int k, bool shuffle)
{
    // Shuffle data
    if (shuffle == 1)
    {
        shuffleRows(data, rows, cols);
    };

    // Iterate k-times
    for (int i = 0; i < k; i++)
    {
        // Create copy of data
        double **array = allocateMatrix(rows, cols);

        for (int j = 0; j < rows; j++)
        {
            memcpy(array[j], data[j], cols * sizeof(double));
        }

        // Swap subarrays in array
        swapSubArrays(array, cols, 0, i);

        // Add array to crossData
        crossData[i] = array;
    };
}

int main()
{
    // Number of folds
    int k = 5;

    // Init shuffle variable
    bool shuffle = true;

    // Initialization of data
    int rows = 5, cols = 2;
    double **data = allocateMatrix(rows, cols);

    // Fill data
    double dt[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            data[i][j] = dt[i * cols + j];
        };
    };

    // Print data
    printf("Matrix data with %d rows and %d cols.\n", rows, cols);
    printMatrix(data, rows, cols, 0);

    // Init result array
    double ***crossData = allocate3dMatrix(k, rows, cols);

    // Create cross data
    createCrossData(data, rows, cols, crossData, k, shuffle);

    // Print cross data
    print3DMatrix(crossData, k, rows, cols, 0);

    // Free memory
    freeMatrix(data, rows);
    free3dMatrix(crossData, k, rows);

    return 0;
}