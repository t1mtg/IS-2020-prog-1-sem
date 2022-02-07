#include <stdio.h>
#include "arch.h"

int main(int argc, char* argv[]) {
    int i;
    char* fileName;
    printf("\n");
    for (i = 0; i < argc; i++) {
        if (argv[i][2] == 'f') {
            fileName = argv[i + 1];
        }
        if (argv[i][2] == 'c') {
            Create(fileName, argc, argv);
            break;
        }
        if (argv[i][2] == 'e') {
            Extract(fileName);
        }
        if (argv[i][2] == 'l') {
            List(fileName);
        }
    }

    return 0;
}
