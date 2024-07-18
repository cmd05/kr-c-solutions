#include <stdio.h>

int main() {
    int c;
    int prev = -1;

    while((c = getchar()) != EOF) {
        if(c == ' ' && prev == ' ')
            continue;
        
        putchar(c);
        prev = c;
    }
}