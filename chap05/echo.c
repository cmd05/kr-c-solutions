#include <stdio.h>

int main(int argc, char* argv[]) {

    // for(int i = 1; i < argc; i++)
    //     printf("%s%s", argv[i], (i < argc-1) ? " " : "");

    while(--argc > 0)
        // printf("%s%s", *(++argv), (argc > 1) ? " " : "");
        printf((argc > 1) ? "%s " : "%s", *(++argv));

    printf("\n");
    return 0;
}