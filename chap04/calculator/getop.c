#include <stdio.h>
#include <ctype.h>
#include "calc.h"

int getop(char s[]) {
    int i, c;
    i = 0;

    while((s[0] = c = getch()) == ' ' || c == '\t') // skip whitespace
                                                    // store first non whitespace in s[0]
        ;

    s[1] = '\0';
    
    if(!isdigit(c) && c != '.') {
        // implement negative numbers
        if(c == '-') {
            int c2 = getch();
            
            if(c2 == ' ' || c2 == '\t')
                return c;
            
            s[1] = c = c2; // assign digit to c
            i = 1;
        } else {
            return c;
        }
    }

    if(isdigit(c)) // collect integer part
        while(isdigit(s[++i] = c = getch()));
    
    if(c == '.') // collect decimal part
        while(isdigit(s[++i] = c = getch()));

    s[i] = '\0';

    if(c != EOF)
        ungetch(c);

    return NUMBER;
}