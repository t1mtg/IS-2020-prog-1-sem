#include <stdio.h>
#include "Ring.h"
int main() {
    struct ring Ring;
    printf("Enter center coords \n");
    scanf("%lf%lf", &Ring.x0, &Ring.y0);
    printf("Enter coords of the point on the 1st circle \n");
    scanf("%lf%lf", &Ring.x1, &Ring.y1);
    printf("Enter coords of the point on the 2nd circle \n");
    scanf("%lf%lf", &Ring.x2, &Ring.y2);
    printf("Perimeter = %lf\n", perimeter(Ring));
    printf("Area = %lf", area(Ring));
    return 0;
}
