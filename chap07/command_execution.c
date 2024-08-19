#include <stdio.h>
#include <stdlib.h>

int main() {
    // system returns a system-dependent integer status from the command executed. In the UNIX
    // system, the status return is the value returned by exit.
    // int n = system("date");
    int n = system("echo hello world");
    printf("%d", n);
}