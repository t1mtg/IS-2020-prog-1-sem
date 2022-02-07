#include <stdio.h>

int main() {
    int a;
    char c;
    scanf("%d", &a);
    c = a >= 88 && a <= 99;
    printf("%d\n", c);
    c = (a >> 10) % 2;
    printf("%d", c);
    return 0;
}
