#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include <fcntl.h>

// get: read n bytes from position pos
int get(unsigned int fd, long pos, char* buf, int n) {
    // The return value from lseek is a long that gives the new position in the file,
    // or -1 if an error occurs.
    if(lseek(fd, pos, 0) >= 0) // get to pos
        return read(fd, buf, n);
    else
        return -1;
}

void error(char* fmt, ...) {
    va_list args;

    va_start(args, fmt);
    fprintf(stderr, "errro: ");
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");
    va_end(args);
    exit(1);
}

int main() {
    int f1;
    char buf[BUFSIZ];

    if((f1 = open("cp.c", O_RDONLY, 0)) == -1)
        error("can't open file");
    
    int pos = 100;
    int n = 20;
    int read_bytes = get(f1, pos, buf, n);

    if(write(1, buf, read_bytes) != read_bytes)
        error("error writing to stdout");
}