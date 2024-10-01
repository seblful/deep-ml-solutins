#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

int main()
{
    // Initialization of parameters
    char kernel = "rbf";
    double lambda_cal = 0.01;
    int iterations = 100;

    // Initialization of data
    int rows = 4, cols = 2;
    double **data = allocateMatrix(rows, cols);

    // Fill data
    double dt[] = {1, 2, 2, 3, 3, 1, 4, 1};

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            data[i][j] = dt[i * cols + j];
        };
    };

    // Print data
    printf("Matrix data with %d rows and %d cols.\n", rows, cols);
    printMatrix(data, rows, cols, 1);

    // Init labels
    int init_labels[] = {1, 1, -1, -1};
    int *labels = (int *)malloc(rows * sizeof(int));

    for (int i = 0; i < rows; i++)
    {
        labels[i] = init_labels[i];
    }

    // Print labels
    printf("Vector y with size %d.\n", rows);
    printIntVector(labels, rows);

    // labels = np.array([]),

    return 0;
}