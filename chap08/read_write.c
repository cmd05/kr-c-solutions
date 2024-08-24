#if __linux
// #include <sys/syscall.h>
#include <stdio.h>
#include <unistd.h>
#elif defined(_WIN32) || defined(_WIN64)
#include <windows.h>       // Or something like it. 
#include <stdio.h>
#endif

// unbuffered input (reads stdin one character at a time)
int my_getchar(void) {
    char c;

    // casting c to unsigned char in the
    // return statement eliminates any problem of sign extension
    return (read(0, &c, 1) == 1) ? (unsigned char) c : EOF; 
}

// buffered version of getchar
int my_getchar_buffered(void) {
    static char buf[BUFSIZ];
    static char* bufp = buf;
    static int n = 0;

    if (n == 0) { // buffer is empty
        n = read(0, buf, sizeof(buf)); // read from fd `0` into `buf`
        bufp = buf; // bufp is a pointer to beginning of buf
    }

    return (--n >= 0) ? 
        (unsigned char) *bufp++ // get next character in buffer
        : EOF; // no more characters left
}

// If the file size is not a multiple of BUFSIZ, some read will return a smaller number of
// bytes to be written by write; 
// the next call to read after that will return zero.

int main() {
    char buf[BUFSIZ];
    int n;

    // while((n = read(0, buf, BUFSIZ)) > 0)
    //     write(1, buf, n);

    int c;
    // while((c = my_getchar()) != EOF)
    while((c = my_getchar_buffered()) != EOF)
        printf("%c", c);

    return 0;
}