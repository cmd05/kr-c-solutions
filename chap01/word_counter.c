#include <stdio.h>

#define OUT 0
#define IN 1

// count lines, words, characters in input 
int main() {
    int nl, nw, nc;
    nl = nw = nc = 0;
    int state = OUT; // inside or outside a word
    int c;

    // This version [(c = getchar()) != EOF] centralizes the input.
    // There is now only one reference to getchar - and shrinks the program.
    // Note: != has higher precedence than `=` so we need the parentheses
    while((c = getchar()) != EOF) {
        if(c == '\n')
            nl++;
        
        if(c == '\t' || c == ' ' || c == '\n')
            state = OUT;
        else if(state == OUT) {
            state = IN;
            nw++;
        }

        ++nc;
    }

    printf("%d %d %d", nl, nc, nw);
}