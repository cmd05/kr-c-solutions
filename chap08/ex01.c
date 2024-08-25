#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#define PERMS 0666 // RW for owner, group, others

void error(int code, char *, ...);

void print_out(unsigned int fd, const char* file) {
    char buf[BUFSIZ];
    int n;

    while((n = read(fd, buf, BUFSIZ)) > 0)
        if(write(1, buf, n) != n)
            error(2, "cat: error writing %s to stdout", file);
}

// cat: concatenate files
int main(int argc, char** argv) {
    char* prog = argv[0];

    if(argc == 1)
        print_out(0, "stdin");
    else
        while(--argc > 0) {
            int f1;
            const char* file = *++argv;

            if((f1 = open(file, O_RDONLY, 0)) == -1)
                error(1, "cp: can't open %s", file);

            print_out(f1, file);
        }
    
    exit(0);
}

void error(int code, char* fmt, ...) {
    va_list args;

    va_start(args, fmt);
    fprintf(stderr, "errro: ");
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");
    va_end(args);
    exit(code);
}