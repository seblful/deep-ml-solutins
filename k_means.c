#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#include "utils.h"

double square(double num)
{
    return num * num;
};

double findDistance(double *point, double *centroid)
{
    // Declare differences and sum
    double diff;
    double sum = 0;

    // Iterate through point and centroid and add distance
    for (int i = 0; i < 2; i++)
    {
        diff = point[i] - centroid[i];
        sum += square(diff);
    };

    return sqrt(sum);
};

void assignPoints(double **points, int p_rows, double **centroids, int k, uint8_t *centroidsIdx)
{
    // Declare value to store distance
    double distance;

    // Create array to store centroids-points distances and assign each value to infinity
    double *centroidsDist = (double *)malloc(p_rows * sizeof(double));
    for (int i = 0; i < p_rows; i++)
    {
        centroidsDist[i] = INFINITY;
    };

    // Assign points
    for (int i = 0; i < p_rows; i++)
    {
        for (int j = 0; j < k; j++)
        {
            distance = findDistance(points[i], centroids[j]);

            // If distance smaller, assign distance and index
            if (distance < centroidsDist[i])
            {
                centroidsDist[i] = distance;
                centroidsIdx[i] = j;
            };
        };
    };
};

double *findMean(double **points, int p_rows, int k, uint8_t *centroidsIdx)
{
    // Create array to store sums of points for each centroid
    double **pointSums = (double **)malloc(k * sizeof(double *));
    for (int i = 0; i < k; i++)
    {
        pointSums[i] = (double *)malloc(2 * sizeof(double));
    };

    // Create array to store number of points for each centroid
    int *pointNums = (int *)calloc(k, sizeof(int));

    // Declare temp index
    uint8_t tempIdx;

    // Add points values to pointSums accordingly to centroidsIdx
    for (int i = 0; i < p_rows; i++)
    {
        tempIdx = centroidsIdx[i];
        pointNums[tempIdx] += 1;
        printf("%u\n", tempIdx);
        for (int j = 0; j < 2; j++)
        {

            pointSums[tempIdx][j] += points[i][j];
        };
    };

    printIntVector(pointNums, 2);
    ;
};

void updateCentroids(double **points, int p_rows, double **centroids, int k, uint8_t *centroidsIdx)
{
    // Declare vector to store means of points for each vector
    double *pointMeans;

    // Calculate mean of points
}

int kMeansClustering(double **points, int p_rows, double **centroids, int k, int max_iterations)
{
    // Create array to store centroids-points indexes
    uint8_t *centroidsIdx = (uint8_t *)malloc(p_rows * sizeof(uint8_t));

    // Assign each point to centroid
    assignPoints(points, p_rows, centroids, k, centroidsIdx);
    printUintVector(centroidsIdx, p_rows);

    // Update centroids
    updateCentroids(points, p_rows, centroids, k, centroidsIdx);
};

int main()
{
    // Initialization of rows and cols in data matrix
    int rows = 6, cols = 2;

    // Initialization of number of clusters (k), number of iterations
    int k = 2;
    int max_iterations = 10;

    // Initialization of points
    double **points = allocateMatrix(rows, cols);

    // Fill points
    double pts[12] = {1, 2, 1, 4, 1, 0, 10, 2, 10, 4, 10, 0};

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            points[i][j] = pts[i * cols + j];
        }
    }

    // Print points
    printf("Matrix points with %d rows and %d cols.\n", rows, cols);
    printMatrix(points, rows, cols, 0);

    // Initialization of centroids
    double **centroids = allocateMatrix(k, 2);

    // Fill centroids
    double cts[4] = {1, 1, 10, 1};

    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            centroids[i][j] = cts[i * k + j];
        }
    }

    // Print centroids
    printf("Matrix centroids with %d rows and %d cols.\n", k, k);
    printMatrix(centroids, k, k, 0);

    // Start k-Means Clustering
    kMeansClustering(points, rows, centroids, k, max_iterations);

    return 0;
}