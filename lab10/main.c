#include <stdio.h>
#include <math.h>
struct Point {
    double x;
    double y;
};

double distance(double x1, double y1, double x2, double y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}


int num_sum(int n) {
    int sum = 0;
    while (n > 0) {
        sum += n % 10;
        n = n / 10;
        num_sum(n);
    }
    return sum;
}

int main() {
    //task 1;
    int n;
    scanf("%d", &n);
    struct Point pnt[n];
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf", &pnt[i].x, &pnt[i].y);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                printf(" X\t ");
            } else {
                double temp = distance(pnt[i].x, pnt[i].y, pnt[j].x, pnt[j].y);
                printf("%.2lf\t ", temp);
            }
        }
        printf("\n");
    }
    //task 2;
    int k;
    scanf("%d", &k);
    int temp = num_sum(k);
    printf(" sum = %d", temp);
    return 0;
}
