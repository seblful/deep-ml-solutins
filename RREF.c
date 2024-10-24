#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

void rref(double **M, size_t rows, size_t cols)
{
    size_t lead = 0;

    for (size_t r = 0; r < rows; r++)
    {
        if (lead >= cols)
            return;

        // Find the pivot row
        size_t i = r;
        while (M[i][lead] == 0)
        {
            i++;
            if (i == rows)
            {
                i = r;
                lead++;
                if (lead == cols)
                    return;
            }
        }

        // Swap the current row with the pivot row
        double *temp = M[r];
        M[r] = M[i];
        M[i] = temp;

        // Normalize the pivot row
        double divisor = M[r][lead];
        for (size_t j = 0; j < cols; j++)
        {
            M[r][j] /= divisor;
        }

        // Eliminate all other entries in this column
        for (size_t k = 0; k < rows; k++)
        {
            if (k != r)
            {
                double factor = M[k][lead];
                for (size_t j = 0; j < cols; j++)
                {
                    M[k][j] -= factor * M[r][j];
                }
            }
        }

        lead++;
    }
}

int main()
{
    // Init M
    size_t rows = 3, cols = 4;
    double init_M[] = {1, 2, -1, -4, 2, 3, -1, -11, -2, 0, -3, 22};
    double **M = allocateMatrix(rows, cols);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            M[i][j] = init_M[i * cols + j];
        }
    }

    printf("Matrix M with %zu rows and %zu cols.\n", rows, cols);
    printMatrix(M, rows, cols, 0);

    // RREF
    rref(M, rows, cols);

    printf("Matrix RREF M with %zu rows and %zu cols.\n", rows, cols);
    printMatrix(M, rows, cols, 0);

    // Free memory
    freeMatrix(M, rows);

    return 0;
}