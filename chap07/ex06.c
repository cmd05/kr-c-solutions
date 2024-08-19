#include <stdio.h>
#include <string.h>

#define MAX_LINE 1000

#define BLUE(string) "\x1b[34m" string "\x1b[0m"
#define RED(string) "\x1b[31m" string "\x1b[0m"

char* my_fgets(char* s, int n, FILE* ifp) {
    register int c;
    register char* cs;

    cs = s;
    while(--n > 0 && (c = getc(ifp)) != EOF)
        if((*cs++ = c) == '\n')
            break;
    
    *cs = '\0';

    return (c == EOF && cs == s /* ifp was at EOF */) ? NULL : s;
}

int getline(char* line, int max) {
    if(my_fgets(line, max, stdin) == NULL)
        return 0; 
    else
        return strlen(line);
}

int main() {
    FILE *f1, *f2;
    f1 = fopen("file1.txt", "r");
    f2 = fopen("file2.txt", "r");
    
    char line1[MAX_LINE];
    char line2[MAX_LINE];
    
    int diff = 0;

    while(1) {
        char* s1 = my_fgets(line1, MAX_LINE, f1);
        char* s2 = my_fgets(line2, MAX_LINE, f2);

        if(strcmp(line1, line2) != 0) {
            diff = 1;
            break;
        }
        
        if(!s1 || !s2)
            break;
    }

    if(diff) {
        printf("--------------------------------\n");
        printf("line_file1:\n" RED("%s") "\n", line1);
        printf("line_file2:\n" BLUE("%s") "\n", line2);
        printf("--------------------------------\n");
    } else {
        printf("File contents are the same!");
    }
}