#include <stdio.h>

int main() {
    int nwhite, nother;
    int ndigits[10] = {0};
    int c;

    while((c = getchar()) != EOF) {
        if(c == ' ' || c == '\t' || c == '\n')
            ++nwhite;
        else if(c >= '0' && c <= '9')
            ++ndigits[c-'0'];
        else
            ++nother;
    }

    int i;
    for(i = 0; i < 10; i++)
        printf("%d - %d\t", i, ndigits[i]);
        
    printf("\nnwhite=%d, nother=%d", nwhite, nother);
}