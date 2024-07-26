#include <stdio.h>
// #include "atof.c"

#define MAXLINE 100

double atof(char []);
int getline(char line[], int max);

/* rudimentary calculator */
int main()
{
    char line[MAXLINE];
    int sum;
    
    
    sum = 0;
    while (getline(line, MAXLINE) > 0)
        printf("\t%g\n", sum += atof(line));
    
    return 0;
}