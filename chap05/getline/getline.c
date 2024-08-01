#include <stdio.h>

// returns length of string (excluding '\0')
int getline(char line[], int max_len) {
    char c;
    int i;

    for(i = 0; (c = getchar()) != EOF && c != '\n' && i < max_len-1; i++) {
        line[i] = c;
        if(c == '\n')
            break;
    }
    
    line[i] = '\0';

    return i;
}