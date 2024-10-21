#include <stdio.h>
#include <stdlib.h>

double relu(float x)
{
    if (x > 0)
    {
        return x;
    };

    return 0;
}

int main()
{
    size_t size = 3;

    double result;

    double inputs[] = {0, 1, -1};
    for (int i = 0; i < size; i++)
    {
        result = relu(inputs[i]);
        printf("Relu of value %.2f is %.2f.\n", inputs[i], result);
    }

    return 0;
}