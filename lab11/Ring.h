#ifndef LAB11_RING_H
#define LAB11_RING_H
#include <math.h>
struct ring {
    double x0, y0; //center coords
    double x1, y1; //coords of the point on the 1st circle
    double x2, y2; //coords of the point on the 2st circle
};

double perimeter (struct ring);
double area (struct ring);

#endif //LAB11_RING_H

