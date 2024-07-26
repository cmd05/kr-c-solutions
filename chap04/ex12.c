#include <stdio.h>
#include <string.h>

/* reverse: reverse string s in place */
void reverse(char s[])
{
    int c, i, j;
    for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
        // c = s[i];
        // s[i] = s[j];
        // s[j] = c;
        c = s[i], s[i] = s[j], s[j] = c;
    }
}

int itoa_i = 0;

// int to string recursive
int itoa_base(int n, char s[]) {
    // static int i = 0;
    unsigned int x;

    if(n < 0) {
        x = -n; // store absolute value of n
        s[itoa_i++] = '-';
    } else {
        x = n;
    }
    
    if(x > 9)
        itoa_base(x / 10, s);
    
    // printf("%d %d\n", x, itoa_i);
    s[itoa_i++] = '0' + (x % 10);
}

void itoa(int n, char s[]) {
    itoa_base(n, s);
    s[itoa_i] = '\0';
}

int main() {
    char s[100] = {0};
    itoa(-123, s);
    printf("%s", s);
}