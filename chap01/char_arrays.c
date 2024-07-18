#include <stdio.h>
#include <string.h>
#define MAXLINE 1000

int getline(char line[], int maxline);
void copy(char to[], char from[]);

// read a line into s and return length
// lenght, lim include the null-terminator
int getline(char s[], int lim) {
    int c, i;

    // for(i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
    //     s[i] = c;

    // ex-18
    i = 0;
    char prev = '\0';
    while(i < (lim - 1) && (c = getchar()) != EOF && c != '\n') {
        if(c == '\t' || (prev == ' ' && c == ' '))
            continue;
        
        s[i] = c;
        prev = c;
        i++;
    }

    if(c == '\n') {
        s[i] = c;
        ++i;
    }

    s[i] = '\0';

    return i; // return length
}

void reverse(char s[]) {
    int len;
    for(len = 0; s[len] != '\0'; len++);

    int i;
    
    for(i = 0; i < len / 2; i++) {
        char tmp = s[i];
        s[i] = s[len-1-i];
        s[len-1-i] = tmp;
    }
}

void copy(char to[], char from[]) {
    int i = 0;

    while((to[i++] = from[i]) != '\0');
        // i++;
}

int main() {
    int len; // current line length
    int max; // maximum length recorded

    char line[MAXLINE];
    char longest[MAXLINE];

    max = 0;

    char s[] = "racecar";
    reverse(s);
    printf(s);
    
    while((len = getline(line, MAXLINE)) != 0) {
        if(len > max) {
            copy(longest, line);
            max = len;
        }
    }

    if(max > 0) // there was a line
        printf("longest: %s", longest);
    
    return 0;
 }