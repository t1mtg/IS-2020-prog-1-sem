#include <stdio.h>
#include <math.h>
int main() {
    double a, z1, z2;
    scanf("%lf", &a);
    z1 = (sin(M_PI / 2 + 3 * a) / (1- sin(3 * a  - M_PI)));
    z2 = 1/tan(5 * M_PI / 4 + 3 * a / 2);
    printf("%lf\n", z1);
    printf("%lf\n", z2);
    return 0;
}
