#include <stdio.h>
#include <stdlib.h>

int main() {
    // void *malloc(size_t n)
        // returns a pointer to n bytes of *uninitialized* storage,
        // or NULL if the request cannot be satisfied.

    // void *calloc(size_t n, size_t size)
        // returns a pointer to enough free space for an array of n objects of the specified size
        // , or NULL if the request cannot be satisfied.
        // calloc() initializes the memory to zero, 

    // int *ip;
    // ip = (int *) calloc(n, sizeof(int));

    // free(p) frees the space pointed to by p,
    // where p was originally obtained by a call to malloc or calloc

    // freeing memory not obtained by `malloc` or `calloc` is a serious error
    // It is also an error to use something after it has been freed.

    // for (p = head; p != NULL; p = p->next /* dereferencing freed memory */) /* WRONG */
    //     free(p);

    // for (p = head; p != NULL; p = q) { // OK
    //     q = p->next;
    //     free(p);
    // }
}