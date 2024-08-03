#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "allocator.h"

#define MAXLINES 5000

typedef struct ARGS {
    unsigned int n : 1;
    unsigned int r : 1;
    unsigned int f : 1;
    unsigned int d : 1;
} ARGS;

char* lineptr[MAXLINES]; // pointers to lines


int getline(char line[], int max_len);
int readlines(char* lineptr[], int maxlines); // returns -1 if input exceeds `maxlines`
void writelines(char* lineptr[], int nlines);

// `comp` is a pointer to a function
// that has two void* arguments
// and returns an int
void my_qsort(void* v[], int left, int right, const ARGS args, int (*comp)(void*, void*, const ARGS args));

// swap at indices n1 and n2 in v
void swap(void* v[], int i, int j);

int numcmp(const char*, const char*, const ARGS args);

int my_strcmp(char*, char*, const ARGS args);

void error_exit(char* msg) {
    if(msg == NULL)
        msg = "Usage: sort\nSupported arguments: n, r, f, d\n";
    
    printf("%s\n", msg);
    exit(-1);
}

int main(int argc, char** argv) {
    int nlines; // number of input lines to read

    // args:
    // 0000 d,f,r,n
    ARGS args;

    // Note: Any pointer (type*) can be cast to void* and back again without loss of information
    
    char c;
    while(--argc > 0 && *(*(++argv)) == '-') {
        while(c = *(++(*(argv))))
            switch(c) {
                case 'n':
                    args.n = 1;
                    break;
                case 'r':
                    args.r = 1;
                    break;
                case 'f':
                    args.f = 1;
                    break;
                case 'd':
                    args.d = 1;
                    break;
                default:
                    error_exit(NULL);
            }
    }

    if((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        // cast both arguments of the function to void*
        // type* to void* is implicit so we do not an explicit cast in this definition
        
        // Note: The *parentheses* around the function name are very important for correct association of the components
        // int *comparison_fn  (void*, void*); // declaration of function that returns an int*, having arguments void*, void*
        // int (*comparison_fn) (void*, void*); // pointer to a function that returns an int, having arguments void*, void*
        
        // warning: pointer type mismatch in conditional expression
        // both types on either side of `:` in ternary expression must be of the same type
        // int (*comparison_fn) (void*, void*) =  (int (*) (void*, void*)) (numeric ? numcmp : strcmp);
        
        int (*comparison_fn) (void*, void*, const ARGS args);
        
        // to avoid ternary expresion warning as above
        if(args.n)
            comparison_fn = (int (*) (void*, void*, const ARGS args)) numcmp; // explicit cast to avoid warning
        else
            comparison_fn = (int (*) (void*, void*, const ARGS args)) my_strcmp;
        
        // writing function name like `numcmp` or `strcmp` by default will give the respective pointer type
        // we don't need to use `&`

        my_qsort((void**) lineptr, 0, nlines-1, args, comparison_fn);
        
        writelines(lineptr, nlines);
        
        return 0;
    } else {
        printf("input to big to sort\n");
        return 1;
    }
}

// Note: The use of parentheses are very important so that the components are
// correctly associated
void my_qsort(void* v[], int left, int right, const ARGS args, int (*comp)(void*, void*, const ARGS args)) {
    int i, last;

    if(left >= right)
        return;

    swap(v, left, (left + right) / 2);

    last = left;
    for(i = left + 1; i <= right; i++)
        if((*comp)(v[i], v[left], args) < 0) // call the comparison function
            swap(v, ++last, i);

    // `comp` -> pointer to function, `*comp` gives the function
        
    swap(v, left, last);
    my_qsort(v, left, last-1, args, comp);
    my_qsort(v, last + 1, right, args, comp);
}

int numcmp(const char* s1, const char* s2, const ARGS args) {
    double v1, v2;
    int res = 0;

    v1 = atof(s1);
    v2 = atof(s2);

    if(v1 < v2)
        res = -1;
    else if(v1 > v2)
        res = 1;

    if(args.r) res *= -1;

    return res;
}

void swap(void* v[], int i, int j) {
    void* temp;
    
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

#define MAXLEN 2000 // max length of line

// returns length of string (excluding '\0')
// getline removes newline character
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

// readlines: read input lines
int readlines(char* lineptr[], int maxlines) {
    int len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;

    while((len = getline(line, MAXLEN)) > 0) // len doesnt include '\0'
        if(nlines >= maxlines || (p = alloc(len+1)) == NULL) { // since nlines starts from 0, it should fail when nlines==maxlines
            return -1;
        } else {
            strcpy(p, line); // write line to heap
            lineptr[nlines++] = p;
        }

    return nlines;
}

char lower(char c) {
    if(c >= 'A' && c <= 'Z')
        return c + ('a' - 'A');
    return c;
}

int is_dir_alpha(char c) {
    return c == ' ' || c == '\t' || isdigit(c) || isalpha(c);
}

int my_strcmp(char* s1, char* s2, const ARGS args) {
    for(;; s1++, s2++) {
        char c1 = *s1;
        char c2 = *s2;

        if(c1 == '\0' || c2 == '\0')
            break;
        
        if(args.f) {
            c1 = lower(c1);
            c2 = lower(c2);
        }

        if(args.d && (!is_dir_alpha(c1) || !is_dir_alpha(c2))) {
            // printf("dir: %c\n", c1, c2);
            continue;
        }

        if(c1 != c2) {
            // printf("break: %c %c\n", c1, c2);
            break;
        }
    }
    
    return *s1 - *s2;
}

// int my_strcmp(char* s1, char* s2, const ARGS args) {
//     for(; *s1 == *s2; s1++, s2++)
//         if(*s1 == '\0') // both *s1 and *s2 are '\0'
//             return 0;
    
//     return *s1 - *s2;
// }

void writelines(char* lineptr[], int nlines) {
    for(int i = 0; i < nlines; i++)
        printf("%s\n", lineptr[i]);
}