#include <stdio.h>
#include <string.h>
#include <limits.h>

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

void itoa(int n, char s[]) {
    unsigned int x;

    if(n < 0)
        x = -n;
    else
        x = n;
        
    int i = 0;

    while(x > 0) {
        int dig = x % 10;
        s[i++] = dig + '0';
        x /= 10;
    }

    if(n < 0)
        s[i] = '-';
    
    s[++i] = '\0'; // null character is not reversed by reverse()
    reverse(s);
}

int main() {
    char s[100] = {0};
    itoa(INT_MIN, s);
    printf("%s", s);
}