#include <stdio.h>

unsigned invert(unsigned int x, int p, int n) {
    return x ^ (~(~0 << n) << (p + 1 - n));
}

int main() {
    unsigned int x = 7893412;
    unsigned int res = invert(x, 4, 3);

    printf("%04x\n", x);
    printf("%04x\n", res);
}