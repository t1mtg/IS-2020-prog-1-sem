#include <stdlib.h>
#include <stdio.h>
#include <string.h>

unsigned int reverseBytes(unsigned int n)
{
    return (n >> 24) | ((n >> 8) & 0x0000ff00) | ((n << 8) & 0x00ff0000) | ((n << 24) & 0xff000000);
}

typedef union tagTAGHEADER
{
    char buffer[12];

    struct {
        unsigned short empty;
        unsigned char version[3];
        unsigned char v1;
        unsigned char v2;
        unsigned char flags;
        unsigned int size;
    } data;
} TAGHEADER;

typedef union tagFRAMEHEADER
{
    char buffer[10];

    struct {
        unsigned char name[4];
        unsigned int size;
        unsigned short flags;
    } data;
} FRAMEHEADER;

void show(char* fileName)
{
    FILE* file;
    file = fopen(fileName, "rb");
    if (file == NULL)
    {
        printf("The file doesn't exist\n");
        exit(1);
    }

    fseek(file, 0, SEEK_SET);

    TAGHEADER tagHeader;
    fread(tagHeader.buffer + 2, sizeof(char), 10, file);
    unsigned int tagSize = reverseBytes(tagHeader.data.size);
    while (ftell(file) < tagSize + 10)
    {
        FRAMEHEADER frameHeader;
        fread(frameHeader.buffer, sizeof(char), 10, file);
        if (frameHeader.data.name[0] == 0)
            break;
        printf("%s: ", frameHeader.data.name);

        unsigned int frameSize = reverseBytes(frameHeader.data.size);

        unsigned char* frameContent;
        frameContent = malloc(sizeof(char) * frameSize);
        fread(frameContent, sizeof(char), frameSize, file);
        unsigned int i;
        for ( i = 0; i < frameSize; ++i)
        {
            printf("%c", frameContent[i]);
        }
        printf("\n");
        free(frameContent);
    }
    fclose(file);
}

void get(char* fileName, char frameName[4])
{
    FILE* file;
    file = fopen(fileName, "rb");

    if (file == NULL)
    {
        printf("The file doesn't exist\n");
        exit(1);
    }

    TAGHEADER tagHeader;
    fread(tagHeader.buffer + 2, sizeof(char), 10, file);

    unsigned int tagSize = reverseBytes(tagHeader.data.size);

    while (ftell(file) < tagSize + 10)
    {
        FRAMEHEADER frameHeader;
        fread(frameHeader.buffer, sizeof(char), 10, file);

        unsigned int frameSize = reverseBytes(frameHeader.data.size);

        if (strcmp(frameHeader.data.name, frameName) == 0)
        {
            printf("%s: ", frameHeader.data.name);

            unsigned char* frameContent;
            frameContent = malloc(sizeof(char) * frameSize);
            fread(frameContent, sizeof(char), frameSize, file);
            unsigned int i;
            for (i = 0; i < frameSize; ++i)
            {
                printf("%c", frameContent[i]);
            }
            printf("\n");
            free(frameContent);
            fclose(file);
            return;
        }

        fseek(file, frameSize, SEEK_CUR);
    }
    fclose(file);
    printf("No value found for %s!", frameName);
}

void copyFile(FILE* input, FILE* output) {
    int c;
    while ((c = getc(input)) != EOF)
        putc(c, output);
}


void set(char* fileName, char frameName[4], char* frameValue)
{
    FILE* file;
    file = fopen(fileName, "rb");

    if (file == NULL)
    {
        printf("The file doesn't exist\n");
        exit(1);
    }

    TAGHEADER tagHeader;
    fread(tagHeader.buffer + 2, sizeof(char), 10, file);

    unsigned int tagSize = reverseBytes(tagHeader.data.size);

    unsigned int oldFramePos = 0;
    unsigned int oldFrameSize = 0;

    while (ftell(file) < tagSize + 10)
    {
        FRAMEHEADER frameHeader;
        fread(frameHeader.buffer, sizeof(char), 10, file);

        unsigned int frameSize = reverseBytes(frameHeader.data.size);

        if (strcmp(frameHeader.data.name, frameName) == 0)
        {
            oldFramePos = ftell(file) - 10;
            oldFrameSize = frameSize;
            break;
        }
        if (frameHeader.data.name[0] == 0){
            break;
        }
        fseek(file, frameSize, SEEK_CUR);
    }

    unsigned int valueSize = strlen(frameValue);
    unsigned int newTagSize = tagSize - oldFrameSize + valueSize + 10 * (oldFramePos == 0);

    if (oldFramePos == 0)
    {
        oldFramePos = ftell(file) - 10;
    }

    if (valueSize == 0)
    {
        newTagSize -= 10;
    }

    FILE* fileCopy;
    fileCopy = fopen("tmp.mp3", "wb");

    fseek(file, 0, SEEK_SET);
    fseek(fileCopy, 0, SEEK_SET);
    copyFile(file, fileCopy);

    fclose(file);
    fclose(fileCopy);

    fileCopy = fopen("tmp.mp3", "rb");
    file = fopen(fileName, "wb");

    tagHeader.data.size = reverseBytes(newTagSize);

    fwrite(tagHeader.buffer + 2, sizeof(char), 10, file);

    fseek(fileCopy, 10, SEEK_SET);
    unsigned int i;
    for (i = 0; i < oldFramePos - 10; ++i)
    {
        int c;
        c = getc(fileCopy);
        putc(c, file);
    }

    if (valueSize > 0)
    {
        FRAMEHEADER frameHeader;
        unsigned int i;
        for (i = 0; i < 4; ++i)
        {
            frameHeader.data.name[i] = frameName[i];
        }
        frameHeader.data.size = reverseBytes(valueSize);
        frameHeader.data.flags = 0;
        fwrite(frameHeader.buffer, sizeof(char), 10, file);
    }

    fwrite(frameValue, sizeof(char), valueSize, file);

    fseek(fileCopy, oldFramePos + 10 + oldFrameSize, SEEK_SET);
    for (i = ftell(file); i < newTagSize; ++i)
    {
        unsigned short int c;
        c = getc(fileCopy);
        putc(c, file);
    }

    printf("New value for frame %s: %s\n", frameName, frameValue);

    copyFile(fileCopy, file);

    fclose(file);
    fclose(fileCopy);
    remove("tmp.mp3");
}

int main(int argc, char* argv[]) {
    char* fileName;
    char* frameName;
    char* value;
    char showFlag = 0;
    char setFlag = 0;
    char getFlag = 0;
    int i;
    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--show") == 0) {
            showFlag = 1;
            continue;
        }
        if (argv[i][2] == 'f')
        {
            fileName = strpbrk(argv[i], "=") + 1;
        }
        if (argv[i][2] == 'g') {
            getFlag = 1;
            frameName = strpbrk(argv[i], "=") + 1;
            continue;
        }
        if (argv[i][2] == 's') {
            setFlag = 1;
            frameName = strpbrk(argv[i], "=") + 1;
            continue;
        }
        if (argv[i][2] == 'v') {
            value = strpbrk(argv[i], "=") + 1;
            continue;
        }
    }

    if (showFlag)
    {
        show(fileName);
    }
    if (getFlag)
    {
        get(fileName, frameName);
    }
    if (setFlag)
    {
        set(fileName, frameName, value);
    }

    return 0;
}