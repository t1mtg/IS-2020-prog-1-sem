#include <stdio.h>
#include <stdlib.h>
int main(int argc, char* argv[]){
    char *num1 = argv[1];
    char *num2 = argv[2];
    char* filename = argv[3];
    int N1 = atoi (num1);
    int N2 = atoi (num2);
    freopen(filename, "w", stdout);
    printf("%d", N1 + N2);
    return 0;
}

