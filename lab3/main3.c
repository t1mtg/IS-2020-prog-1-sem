#include <stdio.h>

int main() {
    int a,b;
    scanf("%o", &a); //1
    printf("%d\n", a); //2
    printf("%x %x\n", a, a << 2); //3
    printf("%x %x\n", a, ~a); //4
    scanf("%x", &b);
    printf("%x\n", a^b); //5
    return 0;
}
