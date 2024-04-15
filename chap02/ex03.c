// Exercise 2-3. Write a function htoi(s), which converts a string of hexadecimal digits
// (including an optional 0x or 0X) into its equivalent integer value. The allowable digits are 0
// through 9, a through f, and A through F.

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char str[] = "0X1";
    int len = strlen(str);

    int i = 0;
    
    if(len >= 2 && str[0] == '0' && (str[1] == 'x' || str[1] == 'X')) {
        if(len == 2) {
            printf("Invalid format");
            return -1;
        }
        
        i = 2;
    }

    int n = 0;

    for(; i < len; i++) {
        char c = tolower(str[i]);

        if(c >= '0' && c <= '9')
            n = 16 * n + (c - '0');
        else if(c >= 'a' && c <= 'f')
            n = 16 * n + (10 + (c - 'a'));
    }

    printf("\n%d", n);
}