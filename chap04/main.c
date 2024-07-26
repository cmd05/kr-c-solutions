#include <stdio.h>

// preprocessor statements - first step in compilation
// #include, to include the contents of a file during compilation,
// and #define, to replace a token by an arbitrary sequence of characters

// any line in the form - #include "filename" - is replaced by the contents of the file 'filename'
// If the filename is quoted, searching for the file
// typically begins where the source program was found; if it is not found there, or if the name is
// enclosed in < and >, searching follows an implementation-defined rule to find the file.
// Naturally, when an included file is changed, all files that depend on it must be recompiled.

// Macro Substitutions
// Substitutions are made only for tokens, and do not take place within quoted
// strings. For example, if YES is a defined name, there would be no substitution in
// printf("YES") or in YESMAN
// Note: macro substitution operates on tokens. 
// ex: int and uint32_t are different tokens. 
// so a macro, 
//    #define int short
// will not replace the `int` portion here- ex: uint32_t x = 40;

#define YES 1000
#define YESMAN 10

// If, however, a parameter name is
// preceded by a # in the replacement text, the combination will be expanded into a quoted string
// with the parameter replaced by the actual argument.
// Within the actual argument, each " is replaced by \" and each \ by \\, so the result is a legal
// string constant.

// ex: dprint(x/y)
// becomes printf("x/y" " = %g\n", x/y);
// after strings are concatenated: (compiler automatically does it)
// printf("x/y = %g\n", x/y);
#define dprint(expr) printf(#expr " = %g\n", expr)

// Each occurrence of a formal parameter (here A or B) will be replaced by the corresponding actual argument.
// ex: x = max(p+q, r+s); becomes
// x = ((p+q) > (r+s) ? (p+q) : (r+s));
// be careful, with multiple evaluations when using macros
// ex: max(i++, j++), with macro will increment the larger quantity twice
#define max(A, B) ((A) > (B) ? (A) : (B))

// the ## and surrounding white space are removed, and the result is re-
// scanned.
#define paste(front, back) front ## back
// creates the token: name1

#define swap(t,x,y) {t z; z = x; x = y; y = z;} // use block structure so that `z` does not leak to scope where swap is called

// provides a way to include code selectively, depending on the value
// of conditions evaluated during compilation.

// A similar style can be used to avoid including files
// multiple times. If this style is used consistently, then each header can itself include any other
// headers on which it depends, without the user of the header having to deal with the
// interdependence.

#if SYSTEM == SYSV
    #define HDR "sysv.h"
#elif SYSTEM == BSD
    #define HDR "bsd.h"
#elif SYSTEM == MSDOS
    #define HDR "msdos.h"
#else
    #define HDR "default.h"
#endif

// The #if line evaluates a constant integer expression (which may not include sizeof, casts, or
// enum constants)
// If the expression is non-zero, subsequent lines until an #endif or #elif or
// #else are included.
// The expression
// defined(name) in a #if is 1 if the name has been defined, and 0 otherwise.
#if !defined(HDR)
#define HDR

// contents of hdr.h go here
// The first inclusion of hdr.h defines the name HDR; subsequent inclusions will find the name
// defined and skip down to the #endif

#endif

// The #ifdef and #ifndef lines are specialized forms that test whether a name is defined.
// #ifndef HDR
// #define HDR
// /* contents of hdr.h go here */
// #endif

// #include HDR

// For external and static variables, the initializer must be a constant expression; the
// initialization is done once, conceptionally before the program begins execution.
int G_X = 100;
// int G_Y = G_X; // error: initializer element is not constant
// int G_Z = 1.0; // will give error: redefinition of 'G_Z' ahead
int G_Z; // ok
int G_Z = 20; // ok

// internal static variables provide private,
// permanent storage within a single function.
void fn() {
    // static int x = 2;
    static int x;
    int x2;
    x += 2;
    printf("hi x=%d\n", x);
    printf("hi x2=%d\n", x2);
}

int f(register unsigned m, register long n) { // register in formal parameters of function
    double x;
    register int i;
}

double db1;
double db2;

void f2(double db1) {
    double db2;

    // extern double db1, db2; // gives redeclaration erro

    db1 = 10.5; // assign to the local db1 (which is in the function parameters)
    db2 = 10.2; // assign to the local db2
}

// This in printd(123) the first printd receives the
// argument n = 123. It passes 12 to a second printd, which in turn passes 1 to a third. The
// third-level printd prints 1, then returns to the second level. That printd prints 2, then returns
// to the first level. That one prints 3 and terminates.
/* printd: print n in decimal */

// Recursion may provide no saving in storage, since somewhere a stack of the values being
// processed must be maintained. Nor will it be faster. But recursive code is more compact, and
// often much easier to write and understand than the non-recursive equivalent. Recursion is
// especially convenient for recursively defined data structures like trees,
void printd(int n)
{
    if (n < 0) {
        putchar('-');
        n = -n;
    }
    if (n / 10)
        printd(n / 10);
    putchar(n % 10 + '0');
}

// #undef getchar
// int getchar(void) { ... }

int main() {
    double c1 = 3, d1 = 5;
    dprint(c1 / d1);
    // output: c1 / d1 = 0.6

    int a1 = 10, b1 = 5;
    swap(int, a1, b1);
    printf("a1=%d b1=%d\n", a1, b1);

    printf("%d\n", YESMAN);

    fn();
    fn();
    fn();
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

    // The idea is that register variables are to be placed in machine registers, which may
    // result in smaller and faster programs. But compilers are free to ignore the advice.
    
    // The register declaration can only be applied to automatic variables and to the
    // formal parameters of a function.
    
    // The specific restrictions on number and types of register
    // variables vary from machine to machine.

    register int x;
    register char c;

    // it is not possible to take the address of a register variable
    // main.c:34:5: error: address of register variable 'x' requested
    // register int* p = &x;

    // f2(10.0);
    // printf("%d ", db1);
    // printf("%d\n", db2);

    // In the absence of explicit initialization, external and static (both global static and local static) variables (both internal and global static variables)
    // are guaranteed to be initialized to zero; automatic and register variables have undefined (i.e., garbage) initial
    // values.

    printf("G_Z=%d\n", G_Z);

    // If there are fewer initializers for an array than the specified size, the others will be zero for
    // external, static and automatic variables. 
    // It is an error to have too many initializers.
    int array[12] = {[0] = 1, [4] = 2, [8] = 3}; // designated initializer in c99
                                                 // rest are zero initialized

    char* pattern1 = "ould";
    char pattern2[] = "ould";
    // char pattern[] = { 'o', 'u', 'l', 'd', '\0' }; // same as pattern2[]
    
    // pattern1[0] = 'c'; // segmentation fault, the string constant is read only memory
    pattern2[0] = 'c'; // ok, we can modify elements of the array

    // when array is passed as a function parameter, it decays to a pointer to its first element
    // hence, we have to pass the size as a seperate parameter
}