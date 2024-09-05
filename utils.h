#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void printMatrix(double **m, int rows, int cols, int precision);
void printVector(double *v, int n, int precision);
void printUintVector(uint8_t *v, int n);
void printIntVector(int *v, int n);

double **allocateMatrix(int rows, int cols);
void freeMatrix(double **matrix, int rows);

double *matrixVectorMultiply(double **M, int rows, int cols, double *v, int n, double *result);
void matrixMultiply(double **A, int rowsA, int colsA, double **B, int rowsB, int colsB, double **C);
double **transposeMatrix(double **matrix, int rows, int cols);

#endif