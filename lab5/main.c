#include <stdio.h>

int main() {
    int a[6] = {0, 3, 5, 7, 11, 13};
    for (int i = 0; i < 6; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
    printf("\n");
    int const n = 2;
    int m1[2][2] = {1, 0, 1, 4};
    int m2[2][2] = {1, 2, 0, 1};
    int res[2][2] = {0};
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                res[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            printf("%d ", res[i][j]);
        }
        printf("\n");
    }
    return 0;
}
