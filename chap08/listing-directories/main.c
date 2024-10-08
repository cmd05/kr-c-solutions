// #include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>     // flags for read and write
#include <sys/types.h> // typedefs
#include <sys/stat.h>  // structure returned by stat 

#include "dirent.h"
#include "fsize.h"

// void fsize(char *);

// print file name
int main(int argc, char **argv) {
    if(argc == 1)   // default: current directory
        fsize(".");
    else
        while(--argc > 0)
            fsize(*++argv);

    return 0;
}