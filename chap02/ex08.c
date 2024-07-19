#include <stdio.h>

unsigned rightrot(unsigned x, int n) {
    int uint_size = sizeof(unsigned int) * 8;
    return ((x & ~(~0 << n)) << (uint_size - n)) | (x >> n);
}

int main() {
    unsigned int x = 541;
    unsigned int res = rightrot(x, 3);

    printf("%04x\n", x);
    printf("%04x\n", res);
}