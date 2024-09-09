#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

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
        int temp = array[a][i];
        array[a][i] = array[b][i];
        array[b][i] = temp;
    }
};

void createCrossData(double **data, int rows, int cols, int k, double ***crossData)
{
    for (int i = 0; i < k; i++)
    {
        // Create copy of data
        double **array = allocateMatrix(rows, cols);

        for (int j = 0; j < rows; j++)
        {
            array[j] = data[j];
        }

        // Swap subarrays in array
        swapSubArrays(array, cols, 0, i);

        // Add array to crossData
    };
};

int main()
{
    // Number of folds
    int k = 5;

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
    createCrossData(data, rows, cols, k, crossData);

    return 0;
}