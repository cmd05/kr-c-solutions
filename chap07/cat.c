#include <stdio.h>

// copy ile
void filecopy(FILE* ifp, FILE* ofp) {
    int c;

    while((c = getc(ifp)) != EOF)
        putc(c, ofp);
}

// cat: concatenate files
int main(int argc, char** argv) {
    FILE* fp;
    char* prog = argv[0];

    if(argc == 1)
        filecopy(stdin, stdout);
    else
        while(--argc > 0)
            if((fp = fopen(*++argv, "r")) == NULL) { // point to next string and check and so on
                // stderr prints to screen even if output of program is piped
                fprintf(stderr, "%s: can't open %s\n", prog, *argv);
                exit(1); // exit automatically calls fclose(), flushing out any buffered output
            } else {
                filecopy(fp, stdout);
                fclose(fp);
            }
    
    // ferror - non zero value on error
    if(ferror(stdout)) {
        fprintf(stderr, "%s: error: writing to stdout\n", prog);
        exit(2);
    }
    
    exit(0);
}