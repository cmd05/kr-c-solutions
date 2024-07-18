#include <stdio.h>

// including '\0'
#define MAX_LEN 1000

char line[MAX_LEN];
char longest[MAX_LEN];
int max = 0;

// If the definition of the external variable occurs
// in the source file before its use in a particular function, then there is
// no need for an extern declaration in the function.

// returns length of string (excluding '\0')
int getline(void) {
    // extern char line[]; // extern declaration is optional since `line` is part of the same program
    char c;
    int i;

    for(i = 0; (c = getchar()) != EOF && c != '\n' && i < MAX_LEN-1; i++) {
        line[i] = c;
        if(c == '\n')
            break;
    }
    
    line[i] = '\0';

    return i;
}

void copy(void) {
    for(int i = 0; longest[i] = line[i]; i++);
}

int main() {
    int len;
    while((len = getline()) > 0) {
        if(len > max) {
            max = len;
            copy();
        }
    }

    printf(longest);
}