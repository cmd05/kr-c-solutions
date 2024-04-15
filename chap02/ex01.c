// Exercise 2-1. Write a program to determine the ranges of char, short, int, and long
// variables, both signed and unsigned, by printing appropriate values from standard headers
// and by direct computation. Harder if you compute them: determine the ranges of the various
// floating-point types.

#include <stdio.h>
#include <limits.h>

int main() {
    printf("%d %d\n", CHAR_MIN, CHAR_MAX);
    printf("%d %d\n", SCHAR_MIN, SCHAR_MAX);
    printf("%d %d\n", SHRT_MIN, SHRT_MAX);
    printf("%ld %lu\n", LONG_MAX, ULONG_MAX);
    printf("%llu\n", ULLONG_MAX);

    printf("UINT_MAX %u\n", ((unsigned int) ~0));
    printf("INT_MAX %d\n", ((unsigned int) ~0) >> 1);
    
    printf("INT_MIN %d\n", -(((unsigned int) ~0) >> 1) -1);
    printf("INT_MIN %d", ~(((unsigned int) ~0) >> 1));
}