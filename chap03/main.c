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

int main() {
    // Switch Case
    // int c, i, nwhite, nother, ndigit[10];
    // nwhite = nother = 0;
    
    // for (i = 0; i < 10; i++)
    //     ndigit[i] = 0;

    //     while ((c = getchar()) != EOF) {
    //     switch (c) {
    //         case '0': case '1': case '2': case '3': case '4':
    //         case '5': case '6': case '7': case '8': case '9':
    //             ndigit[c-'0']++;
    //             break;
    //         case ' ':
    //         case '\n':
    //         case '\t':
    //             nwhite++;
    //             break;
    //         default:
    //             nother++;
    //         break;
    //     }
    // }
    
    // printf("digits =");

    // for (i = 0; i < 10; i++)
    //    printf(" %d", ndigit[i]);
    
    // printf(", white space = %d, other = %d\n", nwhite, nother);

    // int n = 1;

    // cases fall through if there is no break / return statement
    // switch(n) {
    //     case 1:
    //     case 2:
    //         printf("a");
    //         // break;
    //     case 3:
    //         printf("b");
    //         break;
    //     default:
    //         printf("c");
    //         break;
    // }

    // if(5 > 0) {
    //     goto label;
    //     printf("something");
    // } else {
    //     label: // yikes
    //     printf("here we go");
    // }
}