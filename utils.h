#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void printMatrix(double **m, int rows, int cols, int precision);
void print3DMatrix(double ***m, int x, int y, int z, int precision);
void printVector(double *v, int n, int precision);
void printUintVector(uint8_t *v, int n);
void printIntVector(int *v, int n);

double **allocateMatrix(int rows, int cols);
double ***allocate3dMatrix(int x, int y, int z);
void freeMatrix(double **matrix, int rows);
void free3dMatrix(double ***arr, int x, int y);

void scalarVectorMultiply(double *v, size_t n, double value);
void scalarVectorDivision(double *v, size_t n, double value);
double *matrixVectorMultiply(double **M, int rows, int cols, double *v, int n, double *result);
void matrixVectorDotProduct(double **M, size_t rows, size_t cols, double *v, int n, double *result);
void matrixMultiply(double **A, int rowsA, int colsA, double **B, int rowsB, int colsB, double **C);
double **transposeMatrix(double **matrix, int rows, int cols);

#endif