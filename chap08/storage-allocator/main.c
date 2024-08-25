#include "malloc.h"
#include <stdio.h>

int main() {
    int* p = (int *) my_malloc(10 * sizeof(int));
    *p = 55;
    printf("%d", *p);
}