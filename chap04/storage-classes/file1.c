#include <stdio.h>

extern void f(void);

int x = 10; // this has external linkage by default
            // `extern` keyword is not used in the definition (definition -> where memory is set aside)
            // here, memory is allocated
// x = 20; // error: redefinition of 'x'

// extern int y; // error
static int y; // static (global) variables are only accessible by the translation unit where it is defined
              // the `y` variables are independent in file1.c and file2.c

const int z = 30; // here constants also have external linkage by default
                  // file2.c gives the same value for `extern const int z`


int w = 100;
// int w = 20; // file1.c: error: redefinition of 'w'

int a = 2900;
int b = 4500;

int c = 330;

// register int d = 50; // a global-scope declaration may not have this storage class

void myfn() {
    // static int x = 2;
    static int x;
    int x2;
    x += 2;
    printf("hi x=%d\n", x);
    printf("hi x2=%d\n", x2);
}

int main() {
    int a = 15;
    double b = 22; // inside the function, `b` will always refer to `double b` 

    printf("file1.c: a=%d\n", a); // here `a` refers to the local variable `a`
    printf("file1.c: b=%f\n", b); // here `b` refers to the local variable `b`

    printf("file1.c: x=%d\n", x);
    printf("file1.c: y=%d\n", y);
    printf("file1.c: z=%d\n", z);
    printf("file1.c: w=%d\n", w);
    
    c = 250; // `c` refers to the global variable `c`
    printf("file1.c: c=%d\n", c);

    printf("\n");
    
    f(); // f(), will also print the new value of `c`, which is accessed through extern in file2.c

    // OUTPUT:
    // file1.c: a=15
    // file1.c: b=22.000000
    // file1.c: x=10
    // file1.c: y=0
    // file1.c: z=30
    // file1.c: w=100
    // file1.c: c=250

    // file2.c: x=10
    // file2.c: y=20
    // file2.c: z=30
    // file2.c: c=250


    printf("\n\n\n");

    myfn();
    myfn();
    myfn();
    // OUTPUT:
    // when: static int x = 2;
    // hi x=4
    // hi x=6
    // hi x=8

    // when: just static int x;
    // internal static variables are 0 initialized
    // hi x=2
    // hi x2=32759
    // hi x=4
    // hi x2=32759
    // hi x=6
    // hi x2=32759
}