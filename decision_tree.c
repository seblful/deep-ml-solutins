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

double calculateIG(char data[DATA_LENGTH][NUM_ATTRIBUTES][MAX_STR_LENGTH],
                   uint8_t results[DATA_LENGTH],
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

        uint8_t wordResults[DATA_LENGTH];
        int counter = 0;
        int n = 0;

        for (int j = 0; j < DATA_LENGTH; j++)
        {
            if (strcmp(wordSet[k], data[j][i]) == 0)
            {
                wordResults[n] = results[j];
                n += 1;
            };
        };

        double p = (double)n / DATA_LENGTH;

        tSum += p * calculateEntropy(wordResults, n);
    }

    return entropy - tSum;
}

void createWordSet(char data[DATA_LENGTH][NUM_ATTRIBUTES][MAX_STR_LENGTH], char wordSet[SET_LENGTH][MAX_STR_LENGTH], int i)
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

void createDecisionTree(char data[DATA_LENGTH][NUM_ATTRIBUTES][MAX_STR_LENGTH], uint8_t results[DATA_LENGTH])
{
    double infGain;
    double entropy = calculateEntropy(results, DATA_LENGTH);

    for (int i = 0; i < NUM_ATTRIBUTES; i++)
    {
        char wordSet[SET_LENGTH][MAX_STR_LENGTH] = {"", "", ""};
        createWordSet(data, wordSet, i);

        infGain = calculateIG(data, results, wordSet, entropy, i);
        printf("%f\n", infGain);
    }
}

int main()
{
    // Init data
    char data[DATA_LENGTH][NUM_ATTRIBUTES][MAX_STR_LENGTH] = {
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

    uint8_t results[DATA_LENGTH] = {0, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0};

    // Init and fill attribute struct
    char properties[NUM_ATTRIBUTES][MAX_STR_LENGTH] = {"Outlook", "Temperature", "Humidity", "Wind"};

    // Create decision tree
    createDecisionTree(data, results);
}
