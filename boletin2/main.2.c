#include <stdio.h>
#include <math.h>

// Main function
int main() {
    float n = 90;
    float accuracy = 0.0001, denominator, sinx, sinval;

    // Converting degrees to radian
    n = n * (3.142 / 180.0);

    float x1 = n;

    // maps the sum along the series
    sinx = n;

    // holds the actual value of sin(n)
    sinval = sin(n);
    int i = 1;
    do
    {
        denominator = 2 * i * (2 * i + 1);
        x1 = -x1 * n * n / denominator;
        sinx = sinx + x1;
        i = i + 1;
    } while (accuracy <= fabs(sinval - sinx));
    printf("%f", sinx);
    
    return 0;
}
