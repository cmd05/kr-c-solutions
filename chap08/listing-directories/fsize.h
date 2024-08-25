#ifndef FSIZE_H
#define FSIZE_H

#include "dirent.h"

#define MAX_PATH 1024

void fsize(char *name);
void dirwalk(char *dir, void (*fcn) (char *));
MY_DIR *my_opendir(char *dirname);
void my_closedir(MY_DIR *dp);
Dirent *my_readdir(MY_DIR *dp);

#endif