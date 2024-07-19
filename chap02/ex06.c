#include <stdio.h>

unsigned int setbits(unsigned x, int p, int n, int y) {
    return (x & ~(~(~0 << n) << (p + 1 - n))) | ((y & ~(~0 << n)) << (p + 1 - n));
}

int main() {
    unsigned int x = 7893412;
    unsigned int y = 1234;
    unsigned int res = setbits(x, 4, 3, y);

    printf("%04x\n", x);
    printf("%04x\n", y);
    printf("%04x\n", res);
}