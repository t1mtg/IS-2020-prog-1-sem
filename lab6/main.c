#include <stdio.h>
#include <stdlib.h>
int main() {
    const int n = 4;
    int a[n];
    //task1
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    for (int i = 0; i < n; i++) {
        printf("%d ", *(a + i));
    }
    //task2
    int *b;
    b = (int*)malloc(n * sizeof(int));
    printf("\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", b + i);
    }
    for (int i = 0; i < n; i++) {
        printf("%d ", *(b + i));
    }
    free(b);
    return 0;
}