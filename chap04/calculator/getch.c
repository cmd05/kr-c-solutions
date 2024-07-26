#include <stdio.h>
// #include "calc.h"

#define BUFSIZE 100

// we could have used a single character for ungetch
// here we have used a buffer only to show a more general implementation

// external static variable cannot be seen by other source files
static char buf[BUFSIZE];  // buffer for characters which we ungetch
static int bufp = 0; // next free position in `buf`

int getch(void) {
    // read all the characters from ungetch first
    // if empty then do getchar - from the stdio input buffer
    return (bufp > 0) ? buf[--bufp] : getchar(); // getchar gets character one by one from the input buffer, after enter / eof is sent. 
}

void ungetch(int c) {
    if(bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}