#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

double **standardizeData(double **data) {};

double **normalizeData(double **data) {};

int main()
{
    // Declaration of rows and cols in data matrix
    int rows = 3, cols = 2;

    // Init data
    double **data = allocateMatrix(rows, cols);

    // Fill data
    data[0][0] = 1;
    data[0][1] = 2;
    data[1][0] = 3;
    data[1][1] = 4;
    data[2][0] = 5;
    data[2][1] = 6;

    // Print data
    printf("Matrix data with %d rows and %d cols.\n", rows, cols);
    printMatrix(data, rows, cols, 0);

    // Init output
    double **st_output, **norm_output;

    // Standatization
    st_output = standardizeData(data);
    // Normalisation
    norm_output = normalizeData(data);
}