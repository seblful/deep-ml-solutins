#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

#define NUM_ATTRIBUTES 4

int main()
{
    char *attributes[NUM_ATTRIBUTES] = {"Outlook", "Temperature", "Humidity", "Wind"};

    // Print attributes
    printf("Array attributes with size %d:\n", NUM_ATTRIBUTES);
    for (int i = 0; i < NUM_ATTRIBUTES; i++)
    {
        printf("%s\n", attributes[i]);
    };
}
