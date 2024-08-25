#ifndef NULL
#define NULL 0
#endif

// most restrictive type
typedef long Align; // for alignment to long boundary

union header {
    struct {
        union header *ptr; // next block if on free list
        unsigned size;  // size of this block
    } s;
    Align x; // instance of most restrictive type to force alignment of blocks
};

typedef union header Header;

// malloc: general purpose storage allocator
void *my_malloc(unsigned nbytes);
static Header *morecore(unsigned nu);
void my_free(void *ap);