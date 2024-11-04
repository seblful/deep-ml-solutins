#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

#define SENTENCES 3
#define WORDS_PER_SENTENCE 6
#define WORD_LENGTH 10

double calculateTf(char corpus[SENTENCES][WORDS_PER_SENTENCE][WORD_LENGTH],
                   char query[WORD_LENGTH])
{
    ;
}

double calculateIdf(char corpus[SENTENCES][WORDS_PER_SENTENCE][WORD_LENGTH],
                    char query[WORD_LENGTH])
{
    ;
}

double calculateTfidf(char corpus[SENTENCES][WORDS_PER_SENTENCE][WORD_LENGTH],
                      char query[WORD_LENGTH])
{
    double tf;
    double idf;
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

    double tfidf = calculateTfidf(corpus, query);

    printf("TF-IDF of query %s in corpus is %0.3f.\n", query, tfidf);

    return 0;
}