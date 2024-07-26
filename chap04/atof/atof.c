#include <ctype.h>
#include <stdio.h>

/* atof: convert string s to double */
double atof(char s[])
{
    double val, power;
    int i, sign;
    
    for (i = 0; isspace(s[i]); i++) /* skip white space */
        ;
    
    sign = (s[i] == '-') ? -1 : 1;
    
    if (s[i] == '+' || s[i] == '-')
        i++;
    
    for (val = 0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');
    
    if (s[i] == '.')
        i++;
    
    for (power = 1.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10;
    }

    return sign * val / power;
}

// returns length of string (excluding '\0')
int getline(char line[], int max_len) {
    // extern char line[]; // extern declaration is optional since `line` is defined before function
    char c;
    int i;

    for(i = 0; (c = getchar()) != EOF && c != '\n' && i < max_len-1; i++) {
        line[i] = c;
        if(c == '\n')
            break;
    }
    
    line[i] = '\0';

    return i;
}
