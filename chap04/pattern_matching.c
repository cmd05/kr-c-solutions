#include <stdio.h>
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
    for(int i = 0; s[i] != '\0'; i++) {
        int k;
        
        for(k = 0; t[k] != '\0' && s[i] != '\0' && s[i] == t[k]; i++, k++)
            ;
        if(k > 0 && t[k] == '\0')
            return i;
    }

    return -1;
}

int main()
{
    char line[MAXLINE];
    int found = 0;
    
    while (getline(line, MAXLINE) > 0)
        if (strindex(line, pattern) >= 0) {
            printf("%s", line);
            found++;
        }
    
    // The pattern-searching program returns a status from main, the number of matches found. 
    // This value is available for use by the environment that called the program
    return found;
}