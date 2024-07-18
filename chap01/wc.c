#include <stdio.h>

#define OUT 0
#define IN 1

int is_blank(char c) {
    return c != ' ' && c != '\t' && c != '\n';
}

int main() {
    int wc;
    int c, prev;
    int state = OUT;

    while((c = getchar()) != EOF) {
        if(is_blank(c))
            state = OUT;
        if(state == OUT && !is_blank(c)) {
            state = IN;
            wc++;
        }
    }

    printf("words=%d", wc);
}