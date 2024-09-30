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

double calculateEntropy(uint8_t *results, int n)
{
    // // print
    // printf("word results: ");
    // for (int i = 0; i < n; i++)
    // {
    //     printf("%d ", results[i]);
    // };
    // printf("\n");

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

double calculateIG(const char ***data,
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

void createWordSet(const char ***data, char wordSet[SET_LENGTH][MAX_STR_LENGTH], int i)
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

void createDecisionTree(const char ***data, uint8_t *results)
{
    double infGain;
    double entropy = calculateEntropy(results, DATA_LENGTH);

    for (int i = 0; i < NUM_ATTRIBUTES; i++)
    {
        char wordSet[SET_LENGTH][MAX_STR_LENGTH] = {"", "", ""};
        createWordSet(data, wordSet, i);

        infGain = calculateIG(data, DATA_LENGTH, results, wordSet, entropy, i);
        printf("%f\n", infGain);
    }
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

    // Print the data
    for (int i = 0; i < DATA_LENGTH; i++)
    {
        for (int j = 0; j < NUM_ATTRIBUTES; j++)
        {
            printf("%s ", data[i][j]);
        }
        printf("\n");
    }

    // Init and fill results
    uint8_t init_results[] = {0, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0};
    uint8_t *results = (uint8_t *)malloc(sizeof(uint8_t) * DATA_LENGTH);
    for (int i = 0; i < DATA_LENGTH; i++)
    {
        results[i] = init_results[i];
    };

    // Create decision tree
    createDecisionTree(data, results);
}
