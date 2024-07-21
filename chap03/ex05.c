#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void itob(int n, char s[], int b) {
    if(b < 2 || b > 26) {
        fprintf(stderr, "Base out of range");
        exit(-1);
    }

    char symbols[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    unsigned int x = (n < 0) ? -n : n; // to handle largest negative value

    int i;
    for(i = 0; x > 0; i++) {
        int dig = x % b;
        char sym = symbols[dig];
        s[i] = sym;
        x /= b;
    }

    if(b == 8) {
        s[i++] = '0';
    } else if(b == 16) {
        s[i++] = 'x'; // since the string is reversed 'x' should be specified before
        s[i++] = '0';
    }

    if(n < 0)
        s[i++] = '-';

    s[i] = '\0';

    strrev(s);
}

int main() {
    int n = -100;
    char s[100] = {0};
    itob(n, s, 8);

    printf("%s", s);
}