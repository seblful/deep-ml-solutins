#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "utils.h"

// Function to calculate power with integer exponent
double power(double base, int exponent)
{
    if (exponent == 0)
        return 1.0;

    double result = 1.0;
    int is_negative = exponent < 0;
    long long exp = llabs((long long)exponent);

    while (exp > 0)
    {
        if (exp & 1)
            result *= base;
        base *= base;
        exp >>= 1;
    }

    return is_negative ? 1.0 / result : result;
}

double objective(double *x)
{
    return power(x[0], 2) + power(x[1], 2);
}

void gradient(double *x, double *g)
{

    g[0] = 2 * x[0];
    g[1] = 2 * x[1];
}

double *adam(double *x,
             size_t size,
             double lr,
             double beta1,
             double beta2,
             double eps,
             int nIterations)
{
    // Declare variables
    double *g = (double *)malloc(size * sizeof(double));
    double *m = (double *)calloc(size, sizeof(double));
    double *m_hat = (double *)calloc(size, sizeof(double));
    double *v = (double *)calloc(size, sizeof(double));
    double *v_hat = (double *)calloc(size, sizeof(double));

    for (int t = 1; t < nIterations + 1; t++)
    {
        gradient(x, g);
        // scalarVectorMultiply(m, size, beta1, m);

        // Calculate m and v
        for (int i = 0; i < size; i++)
        {
            m[i] = (m[i] * beta1) + ((1 - beta1) * g[i]);
            v[i] = (v[i] * beta2) + ((1 - beta2) * power(g[i], 2));
        }

        // Calculate m_hat and v_hat
        for (int i = 0; i < size; i++)
        {
            m_hat[i] = m[i] / (1 - power(beta1, t));
            v_hat[i] = v[i] / (1 - power(beta2, t));
        }

        // Update x
        for (int i = 0; i < size; i++)
        {
            x[i] = x[i] - (lr * m_hat[i] / (sqrt(v_hat[i]) + eps));
        }
    };

    // Free memory
    free(g);
    free(m);
    free(v);
    free(m_hat);
    free(v_hat);
}

int main()
{
    // Parameters
    double lr = 0.001;
    double beta1 = 0.9;
    double beta2 = 0.999;
    double epsilon = 1e-8;
    int nIterations = 10;

    // Init x
    size_t size = 2;
    double *x0 = (double *)malloc(size * sizeof(double));
    x0[0] = 1;
    x0[1] = 1;

    printf("Vector x0 with size %zu.\n", size);
    printVector(x0, size, 1);

    // Adam optimization
    adam(x0, size, lr, beta1, beta2, epsilon, nIterations);

    printf("Vector x with size %zu.\n", size);
    printVector(x0, size, 8);

    // Free memory
    free(x0);

    return 0;
}