#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>

void printMatrix(double **m, int rows, int cols, int precision);
void printVector(double *v, int n, int precision);

double **allocateMatrix(int rows, int cols);
void freeMatrix(int **matrix, int rows);

void matrixMultiply(int **A, int rowsA, int colsA, int **B, int rowsB, int colsB, int **C);
double **transposeMatrix(int **matrix, int rows, int cols);

#endif