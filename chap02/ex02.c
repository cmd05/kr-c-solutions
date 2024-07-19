#include <stdio.h>

int main() {
    int i = 0;
    char c;
    int lim = 10;
    char s[lim];
    
    while(i < lim - 1) {
        c = getchar();
        if(c == EOF)
            break;
        
        s[i] = c;
        i++;
        
        if(c == '\n')
            break;
    }

    s[i] = '\0';

    printf(s, "\n");
}