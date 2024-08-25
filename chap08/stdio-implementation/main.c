#include "_stdio.h"
#include <unistd.h>

int main() {
    int c;
    FILE *fp;
    
    if(fp = fopen("_stdio.h", "r") != NULL)
        // while((c = getc(fp)) != EOF)
        //     write(1, &c, sizeof(c));
        putchar(c);
}