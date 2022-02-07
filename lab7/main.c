#include <stdio.h>
#include <math.h>
//task 2
struct segment {
    int x1;
    int y1;
    int x2;
    int y2;
};

//task 3
    struct device {
        unsigned play:1;
        unsigned pause:1;
        unsigned record:1;
    };

    union Udevice {
        unsigned int value;
        struct device bitfield;
    };



int main() {

    //task1
    enum paint {
        Akvarel,
        Oil,
        Wateremulsion,
        Akril
    };
    enum paint a = Oil;
    printf("%d\n", a);

    //task2;
    float distance;
    struct segment A;
    A.x1 = 1;
    A.y1 = 2;
    A.x2 = 4;
    A.y2 = 8;
    distance = sqrt(pow((A.x2 - A.x1),2) + pow((A.y2 - A.y1),2));
    printf("%f\n", distance);

    //task3;
    int c;
    scanf("%x", &c);
    union Udevice x;
    x.value = c;
    printf("%d %d %d", x.bitfield.record, x.bitfield.pause, x.bitfield.play);

    return 0;
}
