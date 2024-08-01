#include <stdio.h>
#include <string.h>
#include "getline/getline.h"

#define MAXLINE 1000

// find: print lines that match pattern from 1st arg
// find -nx pattern
int main(int argc, char* argv[]) {
    // **NOTE**: 
    // int main(int argc, char* argv[]) 
    // means argv is a `char**` not a `char* argv[]` due *array to pointer decay*
    // i.e it is a pointer to char* not an array of char*'s
    // so ++argv is a legal operation

    // *prefer the form*
    // int main(int argc, char** argv) 

    // for(int i = 0; i < argc; i++)
    //     printf("%s", *(argv++));
    
    // char* a[] = {"hello", "world", "test"};
    // for(int i = 0; i < 3; i++)
    //     printf("%d", *(a++)); // illegal, a is an array and cannot be incremented
    
    char line[MAXLINE];
    long lineno = 0;
    int c, except = 0, number = 0, found = 0;
    
    // testing:
    // -----
    // char* s = "hello world";
    // printf("%c\n", s[0]); // 'h'
    // printf("%s\n", s); // "hello world"
    
    // char* s2 = *(argv); // dereferencing char** gives char*
    // char s3 = *s2; // dereferencing char* gives char 
    // printf("%c\n", s3); // 'h'
    // printf("%c\n", *(argv[0] + 1));
    // -----

    // explanations:
    // (*(++argv))[0] // increment pointer to next char** -> deref char** -> (char*)[0] -> 0-th char
    
    // a[i] is equivalent to *(a + i)
    // *(++argv[0]) // argv[0] gives a current string (char*) -> ++(char*) points to next character in string -> *(char*) gives character at the pointer location

    // alternate form:
    // **++argv // more unreadable, but same functionality
    // while(--argc > 0 && *(*(++argv)) == '-') // compare first character of the string to '-'
        // while(c = *(++(*argv))) // compare characters after '-'
            // switch(c) {
 
    // test all strings which begin with '-'
    while(--argc > 0 && (*(++argv))[0] == '-') // compare first character of the string to '-'
        while(c = *(++argv[0])) // compare characters after '-'
            switch(c) { 
                case 'x':
                    except = 1;
                    break;
                case 'n':
                    number =  1;
                    break;
                default:
                    printf("find: illegal option %c\n", c);
                    argc = 0;
                    found = -1;
                    break;
            }

    // At the end of
    // the loop, if there are no errors, argc tells how many arguments remain unprocessed and argv
    // points to the first of these. (except the program name)

    // after the end of loop argc = 1 (since we skipped the program name argument)
    // argv points to the pattern

    if(argc != 1) {
        printf("Usage: find -x -n pattern\n");
        return -1;
    } else
        while(getline(line, MAXLINE) > 0) { // stops when getline fails
            lineno++; // line numbers start at 1
            if((strstr(line, *argv) != NULL) != except) {
                if(number)
                    printf("%ld:", lineno);
                printf("%s\n", line);
                found++;
            }
        }

    return found;
}