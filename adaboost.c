#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "utils.h"

typedef struct Classifier
{
    double polarity;
    double threshold;
    double feautureIndex;
    double alpha;
} Classifier;

// Creating a node
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
    };

    printf("\n");

    return;
}

node_t *findUniqueValues(double *array, size_t size)
{
    node_t *head = NULL;

    for (int i = size - 1; i >= 0; i--)
    {
        int isUnique = 1;
        node_t *current = head;

        // Check if the value already exists in the linked list
        while (current != NULL)
        {
            if (current->value == array[i])
            {
                isUnique = 0;
                break;
            }
            current = current->next;
        }

        // If unique, add it to the linked list
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
    // Init weights
    double *weights = (double *)malloc(rows * sizeof(double));

    for (int i = 0; i < rows; i++)
    {
        weights[i] = 1 / (double)rows;
    }

    // Init classifiers
    Classifier *clfs = (Classifier *)malloc(nClf * sizeof(Classifier));

    // Allocate memory for feauture
    double *feautureJ = (double *)malloc(rows * sizeof(double));

    // Iterate through each classifier and find threshold
    for (int i = 0; i < nClf; i++)
    {
        // Create new classifier
        Classifier clf = {0};

        // Define minimum error
        double minError = INFINITY;

        for (int j = 0; j < cols; j++)
        {
            // Find unique values
            for (int k = 0; k < rows; k++)
            {
                feautureJ[k] = X[k][j];
            }

            node_t *uniques = findUniqueValues(feautureJ, rows);

            // Iterating through unique values
            while (uniques != NULL)
            {
                double p = 1;

                // Get prediction
                double *prediction = (double *)malloc(rows * sizeof(double));
                for (int k = 0; k < rows; k++)
                {
                    if (feautureJ[k] < uniques->value)
                    {
                        prediction[k] = -1;
                    }
                    else
                    {
                        prediction[k] = 1;
                    }
                }

                // Calculate error
                double error = 0;

                for (int i = 0; i < rows; i++)
                {
                    if (y[i] != prediction[i])
                    {
                        error += weights[i];
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
                    clf.threshold = uniques->value;
                    clf.feautureIndex = j;
                    minError = error;
                }

                // Assign uniques to the next for iteration
                uniques = uniques->next;
            };
        };

        // Calculate alpha
        clf.alpha = 0.5 * log((1 - minError) / (minError + 1e-10));

        // Get final predictions
        double *predictions = createOnes(rows);
        for (int i = 0; i < rows; i++)
        {
            if (clf.polarity * X[i][(int)clf.feautureIndex] < clf.polarity * clf.threshold)
            {
                predictions[i] = -1;
            };
        }

        // Find sum of weights and update them
        double weightSum = 0;
        for (int i = 0; i < rows; i++)
        {
            weightSum += weights[i];
        }

        for (int i = 0; i < rows; i++)
        {
            weights[i] *= exp(-clf.alpha * y[i] * predictions[i]);
            weights[i] /= weightSum;
        }
        printVector(weights, rows, 5);
        // printf("%f ", clf.alpha);
        // printf("%f ", exp(-clf.alpha * y[i] * predictions[i]));
        // printf("SUM W %f\n", weightSum);
        // printVector(predictions, rows, 2);
    }
}

int main()
{
    int nClf = 3;

    // Init X
    size_t rows = 4, cols = 2;
    double init_X[] = {1, 2, 2, 3, 3, 4, 4, 5};
    double **X = allocateMatrix(rows, cols);
    // Fill x
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            X[i][j] = init_X[i * cols + j];
        };
    };

    printf("Matrix X with %d rows and %d cols.\n", rows, cols);
    printMatrix(X, rows, cols, 0);

    // Init y
    double init_y[] = {1, 1, -1, -1};
    double *y = (double *)malloc(rows * sizeof(double));
    // Fill y
    for (int i = 0; i < rows; i++)
    {
        y[i] = init_y[i];
    };

    printf("Vector y with size %d.\n", rows);
    printVector(y, rows, 0);

    // Perform AdaBoost
    Classifier *result = performAdaboost(X, rows, cols, y, nClf);
}