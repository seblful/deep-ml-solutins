#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#include "utils.h"

#define MAX_STR_LENGTH 50
#define DATA_LENGTH 14
#define NUM_ATTRIBUTES 4
#define NUM_RESULTS 2
#define SET_LENGTH 3

// Define a structure for the decision tree node
typedef struct Node
{
    char attribute[MAX_STR_LENGTH];
    struct Node *children[SET_LENGTH];
    char value[MAX_STR_LENGTH];
    int result;
} Node;

// Function to create a new node
Node *createNode(const char *attribute)
{
    Node *node = (Node *)malloc(sizeof(Node));
    strcpy(node->attribute, attribute);
    for (int i = 0; i < SET_LENGTH; i++)
    {
        node->children[i] = NULL;
    }
    node->value[0] = '\0';
    node->result = -1;
    return node;
}

double calculateEntropy(uint8_t *results, int n)
{
    // Find number of positive and negative answers
    int counters[2] = {0, 0};

    for (int i = 0; i < n; i++)
    {
        if (results[i] == 1)
        {
            counters[0] += 1;
        }
        else
        {
            counters[1] += 1;
        };
    };

    double entropy = 0;
    double p;

    for (int i = 0; i < 2; i++)
    {
        p = counters[i] / (double)n;
        if (p != 0)
        {
            entropy += -(p * log2(p));
        }
    }

    return entropy;
}

double calculateIG(char ***data,
                   int dataLength,
                   uint8_t *results,
                   char wordSet[SET_LENGTH][MAX_STR_LENGTH],
                   double entropy,
                   int i)
{
    double tSum = 0;

    for (int k = 0; k < SET_LENGTH; k++)
    {
        if (strcmp(wordSet[k], "") == 0)
        {
            break;
        }

        uint8_t *wordResults = (uint8_t *)calloc(dataLength, sizeof(uint8_t));
        int counter = 0;
        int n = 0;

        for (int j = 0; j < dataLength; j++)
        {
            if (strcmp(wordSet[k], data[j][i]) == 0)
            {
                wordResults[n] = results[j];
                n += 1;
            };
        };

        double p = (double)n / dataLength;

        tSum += p * calculateEntropy(wordResults, n);
    }

    return entropy - tSum;
}

void createWordSet(char ***data, char wordSet[SET_LENGTH][MAX_STR_LENGTH], int i)
{
    int wordSetInd = 0;

    for (int j = 0; j < DATA_LENGTH; j++)
    {
        bool isUnique = true;

        for (int k = 0; k < SET_LENGTH; k++)
        {

            if (strcmp(wordSet[k], data[j][i]) == 0)
            {
                isUnique = false;
                break;
            };
        }

        if (isUnique == true)
        {
            strcpy(wordSet[wordSetInd], data[j][i]);
            wordSetInd += 1;
        }
    }
};

// Function to check if all results are the same
bool allSameResult(uint8_t *results, int dataLength)
{
    for (int i = 1; i < dataLength; i++)
    {
        if (results[i] != results[0])
        {
            return false;
        }
    }
    return true;
}

// Function to find the attribute with the highest information gain
int findBestAttribute(char ***data, int dataLength, uint8_t *results, char wordSet[NUM_ATTRIBUTES][SET_LENGTH][MAX_STR_LENGTH], double entropy)
{
    double maxIG = -1;
    int bestAttribute = -1;

    for (int i = 0; i < NUM_ATTRIBUTES; i++)
    {
        double ig = calculateIG(data, dataLength, results, wordSet[i], entropy, i);
        if (ig > maxIG)
        {
            maxIG = ig;
            bestAttribute = i;
        }
    }

    return bestAttribute;
}

// Recursive function to create the decision tree
Node *createDecisionTreeRecursive(char ***data,
                                  int dataLength,
                                  uint8_t *results,
                                  const char *properties[NUM_ATTRIBUTES],
                                  char wordSet[NUM_ATTRIBUTES][SET_LENGTH][MAX_STR_LENGTH])
{
    // Base case: all examples have the same result
    if (allSameResult(results, dataLength))
    {
        Node *leaf = createNode("Leaf");
        leaf->result = results[0];
        return leaf;
    }

    // Base case: no more attributes to split on
    if (dataLength == 0)
    {
        Node *leaf = createNode("Leaf");
        // Assign the majority result
        int sum = 0;
        for (int i = 0; i < dataLength; i++)
        {
            sum += results[i];
        }
        leaf->result = (sum > dataLength / 2) ? 1 : 0;
        return leaf;
    }

    double entropy = calculateEntropy(results, dataLength);
    int bestAttribute = findBestAttribute(data, dataLength, results, wordSet, entropy);

    Node *root = createNode(properties[bestAttribute]);

    for (int i = 0; i < SET_LENGTH; i++)
    {
        if (strcmp(wordSet[bestAttribute][i], "") == 0)
        {
            break;
        }

        // Create a subset of data and results for the current attribute value
        char ***subsetData = (char ***)malloc(dataLength * sizeof(char **));
        uint8_t *subsetResults = (uint8_t *)malloc(dataLength * sizeof(uint8_t));
        int subsetLength = 0;

        for (int j = 0; j < dataLength; j++)
        {
            if (strcmp(data[j][bestAttribute], wordSet[bestAttribute][i]) == 0)
            {
                subsetData[subsetLength] = data[j];
                subsetResults[subsetLength] = results[j];
                subsetLength++;
            }
        }

        if (subsetLength > 0)
        {
            root->children[i] = createDecisionTreeRecursive(subsetData, subsetLength, subsetResults, properties, wordSet);
            strcpy(root->children[i]->value, wordSet[bestAttribute][i]);
        }

        free(subsetData);
        free(subsetResults);
    }

    return root;
}

// Function to initialize word sets for all attributes
void initializeWordSets(char ***data, char wordSet[NUM_ATTRIBUTES][SET_LENGTH][MAX_STR_LENGTH])
{
    for (int i = 0; i < NUM_ATTRIBUTES; i++)
    {
        createWordSet(data, wordSet[i], i);
    }
}

// Main function to create the decision tree
Node *createDecisionTree(char ***data, uint8_t *results, const char *properties[NUM_ATTRIBUTES])
{
    char wordSet[NUM_ATTRIBUTES][SET_LENGTH][MAX_STR_LENGTH] = {{{0}}};
    initializeWordSets(data, wordSet);
    return createDecisionTreeRecursive(data, DATA_LENGTH, results, properties, wordSet);
}

// Function to print the decision tree
void printDecisionTree(Node *node, int depth)
{
    if (node == NULL)
    {
        return;
    }

    for (int i = 0; i < depth; i++)
    {
        printf("  ");
    }

    if (strcmp(node->attribute, "Leaf") == 0)
    {
        printf("Result: %d\n", node->result);
    }
    else
    {
        printf("%s\n", node->attribute);
        for (int i = 0; i < SET_LENGTH; i++)
        {
            if (node->children[i] != NULL)
            {
                for (int j = 0; j < depth + 1; j++)
                {
                    printf("  ");
                }
                printf("%s: ", node->children[i]->value);
                printDecisionTree(node->children[i], depth + 2);
            }
        }
    }
}

// Function to free the decision tree
void freeDecisionTree(Node *node)
{
    if (node == NULL)
    {
        return;
    }

    for (int i = 0; i < SET_LENGTH; i++)
    {
        freeDecisionTree(node->children[i]);
    }

    free(node);
}

char ***createData(const char *init_data[DATA_LENGTH][NUM_ATTRIBUTES])
{
    // Dynamically allocate memory for data
    char ***data = (char ***)malloc(DATA_LENGTH * sizeof(char **));
    for (int i = 0; i < DATA_LENGTH; i++)
    {
        data[i] = (char **)malloc(NUM_ATTRIBUTES * sizeof(char *));
        for (int j = 0; j < NUM_ATTRIBUTES; j++)
        {
            data[i][j] = (char *)malloc(MAX_STR_LENGTH * sizeof(char));
        }
    };

    // Copy initial data into dynamically allocated array
    for (int i = 0; i < DATA_LENGTH; i++)
    {
        for (int j = 0; j < NUM_ATTRIBUTES; j++)
        {
            strcpy(data[i][j], init_data[i][j]);
        }
    }

    return data;
}

void freeData(char ***data)
{
    for (int i = 0; i < DATA_LENGTH; i++)
    {
        for (int j = 0; j < NUM_ATTRIBUTES; j++)
        {
            free(data[i][j]);
        }
        free(data[i]);
    }
    free(data);
}

int main()
{
    // Init and fill properties
    const char *properties[NUM_ATTRIBUTES] = {"Outlook", "Temperature", "Humidity", "Wind"};

    // Init and fill data
    const char *init_data[DATA_LENGTH][NUM_ATTRIBUTES] = {
        {"Sunny", "Hot", "High", "Weak"},
        {"Sunny", "Hot", "High", "Strong"},
        {"Overcast", "Hot", "High", "Weak"},
        {"Rain", "Mild", "High", "Weak"},
        {"Rain", "Cool", "Normal", "Weak"},
        {"Rain", "Cool", "Normal", "Strong"},
        {"Overcast", "Cool", "Normal", "Strong"},
        {"Sunny", "Mild", "High", "Weak"},
        {"Sunny", "Cool", "Normal", "Weak"},
        {"Rain", "Mild", "Normal", "Weak"},
        {"Sunny", "Mild", "Normal", "Strong"},
        {"Overcast", "Mild", "High", "Strong"},
        {"Overcast", "Hot", "Normal", "Weak"},
        {"Rain", "Mild", "High", "Strong"}};

    char ***data = createData(init_data);

    // Init and fill results
    uint8_t init_results[] = {0, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0};
    uint8_t *results = (uint8_t *)malloc(sizeof(uint8_t) * DATA_LENGTH);
    for (int i = 0; i < DATA_LENGTH; i++)
    {
        results[i] = init_results[i];
    };

    // Create decision tree
    Node *root = createDecisionTree(data, results, properties);

    // Print the decision tree
    printf("Decision Tree:\n");
    printDecisionTree(root, 0);

    // Free the decision tree
    freeDecisionTree(root);

    // Free the data and results
    freeData(data);
    free(results);

    return 0;
}
