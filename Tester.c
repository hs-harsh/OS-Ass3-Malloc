#include "Memory_Allocator.h"
#include<stdio.h>

int main() {
    void *a = MyMalloc(10);
    void *a1 = MyMalloc(10);
    void *a2 = MyMalloc(10);

    // info();
    void *b = MyMalloc(11);
    void *c = MyMalloc(101);

    // void *a3 = MyMalloc(10);
    // void *a4 = MyMalloc(10);
        info();
        printf("\n----------------------------------------\n");
    MyFree(b);

        info();
        printf("\n----------------------------------------\n");

    MyFree(c);
    info();
    void *d = MyMalloc(11);
    info();
    return 0;
}


