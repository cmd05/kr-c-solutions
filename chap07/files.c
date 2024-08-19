#include <stdio.h>

// definition of getchar and putchar using macros
// #define getchar() getc(stdin)
// #define putchar(c) putc((c), stdout)

// possible implementation of `FILE`
// typedef struct {
//    ...
// } FILE;

// fopen declaration
// FILE *fopen( const char *filename, const char *mode );

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

char* my_fputs(char* s, FILE* ofp) {
    int c;

    while(c = *s++)
        putc(c, ofp);

    return ferror(ofp) ? EOF : 0;
}

int getline(char* line, int max) {
    if(my_fgets(line, max, stdin) == NULL)
        return 0; 
    else
        return strlen(line);
}

int main() {
    // FILE - typedef to struct
    // FILE* - pointer to `FILE` struct

    FILE* fp = fopen("file.txt", "r"); // r/w/a ; additional `b` for binary file

    // If a file that does not exist is opened for writing or appending,
    //  it is created if possible.
    // Opening an existing file for writing causes the old contents to be discarded,
    // , while opening for appending preserves them.

    // Trying to read a file that does not exist is an error,
    // Other possible errors: trying to read a file when you don't have permission.
    
    // If there is any error, fopen will return NULL

    // The file pointers stdin and stdout are objects of type FILE *.
    // They are constants, however, not variables, so it is not possible to assign to them.

    // fclose - OS limits programs to maximum number of files it can open simultaneously
    // so we should free file pointers

    // fclose - flushes output buffer for the file pointer

    // Output written on stderr normally appears
    //  on the screen even if the standard output is redirected.

    // char *fgets(char *line, int maxline, FILE *fp)
    // - fgets reads the next input line (including the newline) from file fp
    // into the character array line; at most maxline-1 characters will be read.
    // - The resulting line is terminated with '\0'
    // - Normally fgets returns line; on end of file or error it returns NULL

    // the function fputs writes a string (which need not contain a newline) to a file:
    // int fputs(char *line, FILE *fp)
    // It returns EOF if an error occurs, and non-negative otherwise.
}