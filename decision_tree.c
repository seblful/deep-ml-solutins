#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#include "utils.h"

#define MAX_STR_LENGTH 50
#define DATA_LENGTH 4
#define NUM_ATTRIBUTES 4
#define NUM_RESULTS 2

typedef struct
{
    int id;
    char name[MAX_STR_LENGTH];
    char value[MAX_STR_LENGTH];
} attr;

attr createAttr(int id, char *name, char *value)
{
    attr newAttribute;

    newAttribute.id = id;
    strcpy(newAttribute.name, name);

    return newAttribute;
};

void printAttr(attr attribute)
{

    printf("Attribute id: %d, name: '%s', value: '%s'.\n", attribute.id, attribute.name, attribute.value);
}

float calculateEntropy(uint8_t *results, int n)
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
        entropy += -(p * log2(p));
    }
}

float calculateIG()
{
    ;
}

void createWordSet(char data[DATA_LENGTH][NUM_ATTRIBUTES][MAX_STR_LENGTH], char wordSet[3][50], int i)
{
    int wordSetInd = 0;

    for (int j = 0; j < DATA_LENGTH; j++)
    {
        bool isUnique = true;

        for (int k = 0; k < 3; k++)
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

    for (int i = 0; i < NUM_ATTRIBUTES; i++)
    {
        char wordSet[3][50] = {"", "", ""};
        createWordSet(data, wordSet, i);

        for (int k = 0; k < 3; k++)
        {
            if (strcmp(wordSet[k], "") != 0)
            {
                printf("%s\n", wordSet[k]);
            }
        }
        printf("\n");

        // do smth with set of words
    }
}

int main()
{
    // Init data
    char data[DATA_LENGTH][NUM_ATTRIBUTES][MAX_STR_LENGTH] = {
        {"Sunny", "Hot", "High", "Weak"},
        {"Sunny", "Hot", "High", "Strong"},
        {"Overcast", "Hot", "High", "Weak"},
        {"Rain", "Mild", "High", "Weak"}};

    uint8_t results[DATA_LENGTH] = {0, 0, 1, 1};

    // Init and fill attribute struct
    char properties[NUM_ATTRIBUTES][MAX_STR_LENGTH] = {"Outlook", "Temperature", "Humidity", "Wind"};
    attr *attributes = (attr *)malloc(NUM_ATTRIBUTES * sizeof(attr));
    for (int i = 0; i < NUM_ATTRIBUTES; i++)
    {
        attributes[i] = createAttr(i, properties[i], "");
    }

    // Print attributes
    printf("Array attributes with size %d:\n", NUM_ATTRIBUTES);
    for (int i = 0; i < NUM_ATTRIBUTES; i++)
    {
        printAttr(attributes[i]);
    };

    // Create decision tree
    createDecisionTree(data, results);
}
