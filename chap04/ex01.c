#include <stdio.h>
#include <string.h>
#define MAXLINE 1000 /* maximum input line length */

char pattern[] = "ould";


/* getline: get line into s, return length */
int getline(char s[], int lim)
{
    int c, i;
    i = 0;
    while (--lim > 0 && (c=getchar()) != EOF && c != '\n')
        s[i++] = c;
    
    if (c == '\n')
        s[i++] = c;
    
    s[i] = '\0';
    
    return i;
}

int strindex(char s[], char t[]) {
    int len_s = strlen(s);
    int len_t = strlen(t);
    
    for(int i = len_s - 1; i >= 0; i--) {
        int k;
        
        for(k = len_t - 1; k >= 0 && i >= 0 && s[i] == t[k]; i--, k--)
            ;

        if(k == -1)
            return i;
    }

    return -1;
}

int main()
{
    char line[MAXLINE];
    int found = 0;
    int pos;
    
    while (getline(line, MAXLINE) > 0)
        if ((pos = strindex(line, pattern)) >= 0) {
            printf("found at pos=%d\n", pos);
            found++;
        }
    
    // The pattern-searching program returns a status from main, the number of matches found. 
    // This value is available for use by the environment that called the program
    return found;
}