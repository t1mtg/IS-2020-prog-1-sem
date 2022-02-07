#include "Ring.h"

double perimeter (struct ring Ring) {
    double R1 = sqrt(pow(Ring.x1 - Ring.x0, 2) + pow(Ring.y1 - Ring.y0, 2));
    double R2 = sqrt(pow(Ring.x2 - Ring.x0, 2) + pow(Ring.y2 - Ring.y0, 2));
    double P = 2 * M_PI * (R1 + R2);
    return P;
}
double area (struct ring Ring) {
    double R1 = sqrt(pow(Ring.x1 - Ring.x0, 2) + pow(Ring.y1 - Ring.y0, 2));
    double R2 = sqrt(pow(Ring.x2 - Ring.x0, 2) + pow(Ring.y2 - Ring.y0, 2));
    double S = M_PI * abs((pow(R2, 2) - pow(R1, 2)));
    return S;
}