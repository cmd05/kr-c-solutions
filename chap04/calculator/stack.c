#include <stdio.h>
// #include "calc.h"

#define MAXVAL 100 // maximum depth of val stack

static int sp = 0; // next free stack position
static double val[MAXVAL]; // value stack

// function names are visible to all source files by default when 
// the program is linked
// we can limit the scope of the function to the current source file
// using `static`
void some_function(void) {
    printf("Hello World");
}

// push: push f onto value stack
void push(double f) {
    if(sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

// pop: pop and return top value from stack
double pop(void) {
    if(sp > 0)
        return val[--sp]; // note we just return the value, not overwrite with 0. it is automatically done with the next push
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

void print_top(void) {
    printf("top element: %f\n", val[sp-1]);
    printf("2nd from top element: %f\n", val[sp-2]);
}

void swap_top(void) {
    double tmp = val[sp-2];
    val[sp-2] = val[sp-1];
    val[sp-1] = tmp;
}

void clear_stack(void) {
    while(sp > 0) {
        val[sp] = 0.0;
        sp--;
    }

    val[sp] = 0.0; // clear 0th value
}