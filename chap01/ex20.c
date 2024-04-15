// Write a program detab that replaces tabs in the input with the proper number
// of blanks to space to the next tab stop. Assume a fixed set of tab stops, say every n columns.
// Should n be a variable or a symbolic parameter?

#include <stdio.h>

// including null terminator
#define MAX_LEN 1000

// returns length of string (excluding '\0')
int getline(char line[], int max_len) {
    // extern char line[]; // extern declaration is optional since `line` is defined before function
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

int main() {
    char line[MAX_LEN];
    int len;
    int n = 4;

    while((len = getline(line, MAX_LEN)) > 0) {
        int r = 0;
        for(int i = 0; i < len; i++) {
            if(line[i] == '\t') {
                for(int j = 0; j < n-r; j++)
                    printf("%s", " ");
                r = n;
            } else {
                printf("%c", line[i]);
                
                if(r < n) r++;
                else r = 1;
            }
        }
        
        printf("\n");
    }
}