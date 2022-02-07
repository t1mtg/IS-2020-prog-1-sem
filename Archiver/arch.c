#include "arch.h"
#include <stdio.h>

void Extract(char* fileName) {
    FILE* f_Arc = fopen(fileName, "rb");
    unsigned long long int now = 0;
    unsigned long long int start = 0;
    int chr;
    while ((chr = getc(f_Arc)) != EOF) {
        start++;
        if (chr == '\n')
            break;
    }

    fseek(f_Arc, 0, SEEK_SET);
    char name[128] = { 0 };
    unsigned long long int sizef;
    FILE* f;
    while (fscanf(f_Arc, "file: %s size: %llu ", name, &sizef) != 0) {
        f = fopen(name, "wb");
        if (f == NULL)
            break;
        now = ftell(f_Arc);
        fseek(f_Arc, start, SEEK_SET);
        start += sizef;
        while ((sizef--) > 0) {
            chr = getc(f_Arc);
            putc(chr, f);
        }
        fseek(f_Arc, now, SEEK_SET);
        fclose(f);
    }
    printf("extraction completed");
}

void List(char* file_name) {
    FILE* f_Arc = fopen(file_name, "rb");
    char name[128];
    int i;
    while (1) {
        fscanf(f_Arc, "%s", name);
        if (name[0] == '!')
            break;
        fscanf(f_Arc, "%s", name);
        printf("%s\n", name);
        fscanf(f_Arc, "%s", name);
        fscanf(f_Arc, "%s", name);
    }
    fclose(f_Arc);
}

void Create(char* fileName, int argc, char* argv[]) {
    int i;
    int tmp;
    FILE* f_Arc = fopen(fileName, "wb");
    FILE* f;
    unsigned long long int nameSize[128];
    for (i = 4; i < argc; i++) {
        f = fopen(argv[i], "rb");
        if (f == NULL) {
            continue;
        }
        fseek(f, 0, SEEK_END);
        nameSize[i - 4] = ftell(f);
        fclose(f);
    }
    for (i = 0; i < argc - 4; i++) {
        fprintf(f_Arc, "file: %s size: %llu ", argv[i + 4], nameSize[i]);
    }
    fprintf(f_Arc, "!\n");
    for (i = 4; i < argc; i++) {
        f = fopen(argv[i], "rb");
        if (f == NULL) {
            printf("Open error %s\n", argv[i]);
            continue;
        }
        while ((tmp = getc(f)) != EOF)
            putc(tmp, f_Arc);
        fclose(f);
    }
    printf("archivation finished");
}


