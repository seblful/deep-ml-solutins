#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

#include "utils.h"

#define SENTENCES 3
#define WORDS_PER_SENTENCE 6
#define WORD_LENGTH 10

double *calculateTf(char corpus[SENTENCES][WORDS_PER_SENTENCE][WORD_LENGTH],
                    char query[WORD_LENGTH])
{
    // Allocate memory for tf
    double *tf = (double *)malloc(SENTENCES * sizeof(double));

    for (int i = 0; i < SENTENCES; i++)
    {
        int wordCount = 0;
        int queryCount = 0;

        for (int j = 0; j < WORDS_PER_SENTENCE; j++)
        {

            if (!corpus[i][j][0])
            {
                break;
            }

            wordCount += 1;

            if (strcmp(corpus[i][j], query) == 0)
            {
                queryCount += 1;
            };
        }

        tf[i] = (double)queryCount / (double)wordCount;
    }

    return tf;
}

double calculateIdf(char corpus[SENTENCES][WORDS_PER_SENTENCE][WORD_LENGTH],
                    char query[WORD_LENGTH])
{
    int sentCount = 0;

    for (int i = 0; i < SENTENCES; i++)
    {

        for (int j = 0; j < WORDS_PER_SENTENCE; j++)
        {

            if (!corpus[i][j][0])
            {
                break;
            }

            if (strcmp(corpus[i][j], query) == 0)
            {
                sentCount += 1;
                break;
            }
        }
    }

    return log10((double)SENTENCES / (double)sentCount);
}

double *calculateTfidf(char corpus[SENTENCES][WORDS_PER_SENTENCE][WORD_LENGTH],
                       char query[WORD_LENGTH])
{
    double *tf = calculateTf(corpus, query);
    printf("Vector tf with size %zu.\n", SENTENCES);
    printVector(tf, SENTENCES, 4);
    double idf = calculateIdf(corpus, query);
    printf("IDF is %0.4f.\n", idf);

    // Allocate memory for tfidf
    double *tfidf = (double *)malloc(SENTENCES * sizeof(double));

    return tfidf;
}

int main()
{
    // Init corpus and query
    char corpus[SENTENCES][WORDS_PER_SENTENCE][WORD_LENGTH] = {
        {"the", "cat", "sat", "on", "the", "mat"},
        {"the", "dog", "chased", "the", "cat"},
        {"the", "bird", "flew", "over", "the", "mat"}};

    char query[WORD_LENGTH] = {"cat"};

    // Print strings
    printf("Corpus:\n");
    for (int i = 0; i < SENTENCES; i++)
    {
        for (int j = 0; j < WORDS_PER_SENTENCE; j++)
        {
            printf("%s ", corpus[i][j]);
        }

        printf("\n");
    }

    printf("Query is %s.\n", query);

    double *tfidf = calculateTfidf(corpus, query);

    printf("Vector tfidf with size %zu.\n", SENTENCES);
    printVector(tfidf, SENTENCES, 4);

    // Free memory

    return 0;
}