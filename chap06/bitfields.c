// // The numbers must be powers of two.
// #define KEYWORD 01
// #define EXTERNAL 02
// #define STATIC 04

// alternatively
// enum { KEYWORD = 01, EXTERNAL = 02, STATIC = 04 };

// A bit-field, or field for short, is a set of adjacent bits within a single implementation-defined
// storage unit that we will call a `word.`
struct {
    unsigned int is_keyword : 1;
    unsigned int is_extern : 1;
    // unsigned int : 3; // padding
    unsigned int is_static : 1;
} flags;

int main() {
    // unsigned int flags;
    // flags |= EXTERNAL | STATIC; // turns on the EXTERNAL and STATIC bits in flags
    // flags &= ~(EXTERNAL | STATIC); // turns off the EXTERNAL and STATIC bits in flags

    // if ((flags & (EXTERNAL | STATIC)) == 0) {} // true if both bits are off

    flags.is_extern = flags.is_static = 1; // turn on EXTERNAL and STATIC
    flags.is_extern = flags.is_static = 0; // turn them off

    if (flags.is_extern == 0 && flags.is_static == 0) {} // both are off
}
