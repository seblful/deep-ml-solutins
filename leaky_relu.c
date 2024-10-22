#include <stdio.h>
#include <stdlib.h>

double leakyRelu(double x, double alpha)
{
    if (x > 0)
    {
        return x;
    }

    return alpha * x;
}

int main()
{
    size_t size = 4;

    double result;

    double inputs[] = {0, 1, -1, -2};
    for (int i = 0; i < size; i++)
    {
        result = leakyRelu(inputs[i], 0.01);
        printf("Leaky Relu of value %.2f is %.2f.\n", inputs[i], result);
    }

    return 0;
}
