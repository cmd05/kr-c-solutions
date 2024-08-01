#define ALLOCSIZE 10000

static char allocbuf[ALLOCSIZE]; // storage for alloc
static char* allocp = allocbuf; // next free position

char* alloc(int n) { // returns a pointer to n characters
    // note the buffer always grows towards right and shrinks (by `afree`) leftwards
    // such that the array is always in the form: | used space | free space |

    if(allocbuf + ALLOCSIZE - allocp >= n) { // enough free space for n chars
        allocp += n; // point to next free
        return allocp - n;
    } else {
        // C guarantees that zero is *never a valid address for data*,
        // so a return value of zero can be used to signal an
        // abnormal event, in this case no space.
        return 0; // not enough free space for n chars
    }
}

// free storage at p
void afree(char* p) {
    if(p >= allocbuf && p < allocbuf + ALLOCSIZE) // check bounds
        allocp = p;
}