#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

#define NUM_ATTRIBUTES 4

typedef struct
{
    int id;
    char name[50];
    char value[50];
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

int main()
{
    // Init and fill attribute struct
    char *properties[NUM_ATTRIBUTES] = {"Outlook", "Temperature", "Humidity", "Wind"};
    attr *attributes = (attr *)malloc(NUM_ATTRIBUTES * sizeof(attr));
    for (int i; i < NUM_ATTRIBUTES; i++)
    {
        attributes[i] = createAttr(i, properties[i], "");
    }

    // Print attributes
    printf("Array attributes with size %d:\n", NUM_ATTRIBUTES);
    for (int i = 0; i < NUM_ATTRIBUTES; i++)
    {
        printAttr(attributes[i]);
    };
}
