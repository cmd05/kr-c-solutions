#include <stdio.h>

int main() {
    double nc;

    for(nc = 0; getchar() != EOF; nc++)
        ; // note the semicolon is a seperate statement from the for loop (null statement)

    printf("Number of characters: %.0f", nc);    
}

// Output:

// hello world
// adios
// ^Z
// Number of characters: 18
// i.e "hello world\nadios\n"