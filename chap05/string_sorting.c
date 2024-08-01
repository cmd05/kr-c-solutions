#include <stdio.h>
#include <string.h>
#include "allocator.h"

#define MAXLINES 5000

char* lineptr[MAXLINES]; // array of char*

int readlines(char* lineptr[], int max_lines); // returns number of lines of input, -1 if it exceeds max_lines
void writelines(char* lineptr[], int max_lines);

void swap(char* v[], int i, int j);
void qsort(char* lineptr[], int left, int right);

int getline(char line[], int max_len);

int main() {
    int nlines;
    if((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        qsort(lineptr, 0, nlines-1);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("error: input too big too sort\n");
        return 1;
    }
}

#define MAXLEN 1000 // max length of any input line
int getline(char*, int);

// readlines: read input lines
int readlines(char* lineptr[], int maxlines) {
    int len, nlines;
    char* p, line[MAXLEN];

    nlines = 0;

    while((len = getline(line, MAXLEN)) > 0) // len doesnt include '\0'
        if(nlines >= maxlines || (p = alloc(len)) == NULL) { // since nlines starts from 0, it should fail when nlines==maxlines
            return -1;
        } else {
            // printf("%d\n", nlines);
            line[len-1] = '\0'; // delete newline character
            strcpy(p, line); // write line to heap
            lineptr[nlines++] = p;
        }

    return nlines;
}

// writelines: write output lines
// void writelines(char* lineptr[], int nlines) {
//     int i;

//     for(i = 0; i < nlines; i++)
//         printf("%s\n", lineptr[i]);
// }

// alternative
void writelines(char* lineptr[], int nlines) {
    while(nlines-- > 0)
        printf("%s\n", *lineptr++);
}

// interchange v[i] and v[j]
void swap(char* v[], int i, int j) {
    char* temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

// qsort: sort v[left]...v[right] into increasing order
void qsort(char* v[], int left, int right) {
    int i, last;

    if(left >= right)
        return;

    swap(v, left, (left + right) / 2);
    last = left;
    for(i = left + 1; i <= right; i++)
        if(strcmp(v[i], v[left]) < 0)
            swap(v, ++last, i);

    swap(v, left, last);
    qsort(v, left, last-1);
    qsort(v, last+1, right);
}

// returns length of string (excluding '\0')
int getline(char line[], int max_len) {
    char c;
    int i;

    for(i = 0; (c = getchar()) != EOF && c != '\n' && i < max_len-1; i++) {
        line[i] = c;
        if(c == '\n')
            break;
    }
    
    line[i] = '\0';

    return i;
}