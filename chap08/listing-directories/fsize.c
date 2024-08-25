#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>     // flags for read and write
#include <sys/types.h> // typedefs
#include <sys/stat.h>  // structure returned by stat 
#include <sys/dir.h>

#include "dirent.h"
#include "fsize.h"

#ifndef DIRSIZ
#define DIRSIZ 14
#endif

// Each call to my_readdir returns a pointer to information for the next file, or NULL when there are
// no files left. Each directory always contains entries for itself, called ".", and its parent, "..";
// these must be skipped, or the program will loop forever.

// fsize: print the name of file `name`
void fsize(char *name) {
    struct stat stbuf;

    if(stat(name, &stbuf) == -1) {
        fprintf(stderr, "fsize: can't access %s\n", name);
        return;
    }

    if((stbuf.st_mode & S_IFMT) == S_IFDIR) // AND with S_IFMT to determine the file type
        dirwalk(name, fsize);

    printf("%8ld %s\n", stbuf.st_size, name);
}

// dirwalk: apply fcn to all files in dir
void dirwalk(char *dir, void (*fcn) (char *)) {
    char name[MAX_PATH];
    Dirent *dp; // note dirent maybe a pure file or it can be a directory too
    MY_DIR *dfd;

    if((dfd = my_opendir(dir)) == NULL) {
        fprintf(stderr, "dirwalk: can't open%s\n", dir);
        return;
    }

    while((dp = my_readdir(dfd)) != NULL) {
        if(strcmp(dp->name, ".") == 0 || strcmp(dp->name, ".."))
            continue; // skip self and parent directory
        
        if(strlen(dir) + strlen(dp->name) + 2 > sizeof(name)) // (+2) for '\' and null terminator '\0'
            fprintf(stderr, "dirwalk: name %s %s too long\n", dir, dp->name);
        else {
            sprintf(name, "%s/%s", dir, dp->name);
            // printf("%s/%s", dir, dp->name);
            (*fcn) (name); // call required function for directory entry
        }
    }

    my_closedir(dfd);
}

// my_opendir: open a directory for my_readdir calls
MY_DIR *my_opendir(char *dirname) {
    int fd;
    struct stat stbuf;

    MY_DIR *dp;

    if ((fd = open(dirname, O_RDONLY, 0)) == -1
        || fstat(fd, &stbuf) == -1
        || (stbuf.st_mode & S_IFMT) != S_IFDIR
        || (dp = ((MY_DIR *) malloc(sizeof(MY_DIR)))) == NULL)
        return NULL;
    
    dp->fd = fd;
    return dp;
}

// my_closedir: close directory opened by my_opendir
void my_closedir(MY_DIR *dp) {
    if(dp) {
        close(dp->fd);
        free(dp);
    }
}

// my_readdir: read directory entries in sequence
Dirent *my_readdir(MY_DIR *dp) {
    struct direct dirbuf; // local directory
    static Dirent d;      // return portable struct

    while(read(dp->fd, (char *) &dirbuf, sizeof(dirbuf)) == sizeof(dirbuf)) {
        if(dirbuf.d_ino == 0) // slot in use
            continue;
        
        d.ino = dirbuf.d_ino;
        strncpy(d.name, dirbuf.d_name, DIRSIZ);
        d.name[DIRSIZ] = '\0';

        return &d; // can return address of static variable defined inside function
    }

    return NULL;
}