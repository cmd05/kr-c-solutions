#include <stdio.h>

int main() {
    int c; // getchar() returns an int. we need EOF + range of unsigned char (0-255). So [-1, 255]
    // char c;

    c = getchar();
    while(c != EOF) {
        putchar(c);
        c = getchar();
    }
}