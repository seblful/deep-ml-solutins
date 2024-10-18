#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "utils.h"

typedef struct Classifier
{
    double polarity;
    double threshold;
    int featureIndex;
    double alpha;
} Classifier;

typedef struct node
{
    double value;
    struct node *next;
} node_t;

void printList(node_t *head)
{
    while (head != NULL)
    {
        printf("%.2f ", head->value);
        head = head->next;
    }
    printf("\n");
}

void freeList(node_t *head)
{
    node_t *tmp;
    while (head != NULL)
    {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

node_t *findUniqueValues(double *array, size_t size)
{
    node_t *head = NULL;

    for (int i = size - 1; i >= 0; i--)
    {
        int isUnique = 1;
        node_t *current = head;

        while (current != NULL)
        {
            if (current->value == array[i])
            {
                isUnique = 0;
                break;
            }
            current = current->next;
        }

        if (isUnique)
        {
            node_t *newNode = (node_t *)malloc(sizeof(node_t));
            newNode->value = array[i];
            newNode->next = head;
            head = newNode;
        }
    }

    return head;
}

double *createOnes(size_t size)
{
    double *ones = (double *)malloc(size * sizeof(double));
    for (int i = 0; i < size; i++)
    {
        ones[i] = 1;
    }
    return ones;
}

Classifier *performAdaboost(double **X, size_t rows, size_t cols, double *y, int nClf)
{
    // Init vars
    double *weights = (double *)malloc(rows * sizeof(double));
    for (int i = 0; i < rows; i++)
    {
        weights[i] = 1.0 / rows;
    }

    Classifier *clfs = (Classifier *)malloc(nClf * sizeof(Classifier));
    double *featureJ = (double *)malloc(rows * sizeof(double));

    // Iterate through classifiers
    for (int i = 0; i < nClf; i++)
    {
        double minError = INFINITY;
        Classifier clf = {0};

        for (int j = 0; j < cols; j++)
        {
            // Find unique values
            for (int k = 0; k < rows; k++)
            {
                featureJ[k] = X[k][j];
            }
            node_t *uniques = findUniqueValues(featureJ, rows);

            // Iterating through unique values
            for (node_t *current = uniques; current != NULL; current = current->next)
            {
                // Get prediction
                double p = 1;
                double *prediction = createOnes(rows);

                for (int k = 0; k < rows; k++)
                {
                    if (X[k][j] < current->value)
                    {
                        prediction[k] = -1;
                    }
                }

                // Calculate error
                double error = 0;
                for (int k = 0; k < rows; k++)
                {
                    if (y[k] != prediction[k])
                    {
                        error += weights[k];
                    }
                }

                if (error > 0.5)
                {
                    error = 1 - error;
                    p = -1;
                }

                if (error < minError)
                {
                    clf.polarity = p;
                    clf.threshold = current->value;
                    clf.featureIndex = j;
                    minError = error;
                }

                free(prediction);
            }

            freeList(uniques);
        }

        // Calculate alpha
        clf.alpha = 0.5 * log((1.0 - minError) / (minError + 1e-10));

        // Get final predictions
        double *predictions = createOnes(rows);
        for (int k = 0; k < rows; k++)
        {
            if (clf.polarity * X[k][clf.featureIndex] < clf.polarity * clf.threshold)
            {
                predictions[k] = -1;
            }
        }

        // Update weights
        for (int k = 0; k < rows; k++)
        {
            weights[k] *= exp(-clf.alpha * y[k] * predictions[k]);
        }

        double weightSum = 0;
        for (int k = 0; k < rows; k++)
        {
            weightSum += weights[k];
        }
        for (int k = 0; k < rows; k++)
        {
            weights[k] /= weightSum;
        }

        // Add classifier to array
        clfs[i] = clf;
        free(predictions);
    }

    // Free memory
    free(weights);
    free(featureJ);

    return clfs;
}

int main()
{
    int nClf = 3;
    size_t rows = 4, cols = 2;

    // Init X
    double init_X[] = {1, 2, 2, 3, 3, 4, 4, 5};
    double **X = allocateMatrix(rows, cols);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            X[i][j] = init_X[i * cols + j];
        }
    }

    printf("Matrix X with %zu rows and %zu cols.\n", rows, cols);
    printMatrix(X, rows, cols, 0);

    // Init y
    double init_y[] = {1, 1, -1, -1};
    double *y = (double *)malloc(rows * sizeof(double));
    for (int i = 0; i < rows; i++)
    {
        y[i] = init_y[i];
    }

    printf("Vector y with size %zu.\n", rows);
    printVector(y, rows, 0);

    Classifier *result = performAdaboost(X, rows, cols, y, nClf);

    printf("AdaBoost Results:\n");
    for (int i = 0; i < nClf; i++)
    {
        printf("Classifier %d: polarity = %.2f, threshold = %.2f, feature_index = %d, alpha = %.2f\n",
               i, result[i].polarity, result[i].threshold, result[i].featureIndex, result[i].alpha);
    }

    // Free memory
    freeMatrix(X, rows);
    free(y);
    free(result);

    return 0;
}