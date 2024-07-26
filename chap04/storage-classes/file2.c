#include <stdio.h>

extern int x; // access x since it has external linkage
              // extern is used to access `x` and tells the compiler that x is declared elsewhere
              // note: this extern declaration, brings the identifier into scope. this does not allocate any memory
static int y = 20;

extern const int z;

extern int c;

// int w = 999; // we cannot define an external variable with the same name in another translation unit
// multiple definition of `w'; cc6t21lr.o:file1.c:(.data+0x4): first defined here

void f(void) {
    printf("file2.c: x=%d\n", x);
    printf("file2.c: y=%d\n", y);
    printf("file2.c: z=%d\n", z);
    printf("file2.c: c=%d\n", c);
    // printf("file2.c: w=%d\n", w);
}