#include <stdio.h>
#include <stddef.h>
// 83-114

void f2(int* q) { // note: q is a local variable to f2. f2(p) 
                  // copies the address stored in p, to q like a simple copy-by-value
                  // now we can manipulate `x`, in f2
    *q = 20;
    printf("*q=%d\n", *q);
    q = NULL;
}

// void myf2(int daytab[2][13]);

// More generally, only the first dimension (subscript) of
// an array is free; all the others have to be specified.
// void myf2(int daytab[][13]);

void myf2(int (*daytab)[13]); // pointer to an array of 13 integers
            // The parentheses are necessary since brackets [] have higher precedence than *.                            

/* month_name: return name of n-th month */
char *month_name(int n)
{
    static char *name[] = {
        "Illegal month",
        "January", "February", "March",
        "April", "May", "June",
        "July", "August", "September",
        "October", "November", "December"
    };
    
    return (n < 1 || n > 12) ? name[0] : name[n];
}


// if p and q point to elements of the same array, and p<q, then
// q-p+1 is the number of elements from p to q inclusive.

// The number of characters in the string
// could be too large to store in an int. The header <stddef.h> defines a type ptrdiff_t that
// is large enough to hold the signed difference of two pointer values.

// size_t is the *unsigned integer type* *returned by the sizeof operator*.
size_t strlen(char* s) {
    char* p = s;

    while(*p != '\0')
        p++;

    return p - s;
}

// *s++ - since we use post increment pointer is to same character for the operation,
// then we dereference it
// we don't need parenthesis since postfix operation is run first as we intend to
void __strcpy(char* s, char* t) {
    // while((*s++ = *t++) != '\0')
    //     ;
    while(*s++ = *t++) // or just
        ;
}

int _strcmp(char* s, char* t) {
    for(; *s == *t; s++, t++)
        if(*s == '\0')
            return 0;

    return *s - *t;
}

void f1() {
    int x = 10;
    int *p = &x;
    f2(p);
    printf("*p=%d\n", *p);
}

/* strcpy: copy t to s; pointer version */
void _strcpy(char *s, char *t)
{
    int i;
    i = 0;
    while ((*s = *t) != '\0') {
        s++;
        t++;
    }
}

// When an array name is passed to a function, what is passed is the location of the initial
// element (array-pointer decay). Within the called function, this argument is a *local variable*, 
// *and so an array name
// parameter is a pointer, that is, a variable containing an address.*
void myfn(char s[]) {
    // note s is a pointer which is a local variable
    // to `myfn`
    *s = 'a';
    s++; // legal since, s is a pointer (local to `myfn`) not an array identifier
    *s = 'b';
}

void _strcat(char* s, char* t) {
    while(*s++ != '\0')
        ;
    
    while((*s = *t) != '\0')
        ;
}

void _strncpy(char* s, char* t, unsigned int n) {
    while(n-- > 0 && (*s++ = *t++))
        ;
    
    *s = '\0';
}

void reverse(char* s) {
    // int len = strlen(s);

    // int i = 0, j = len - 1;

    // for(; i < j; i++, j--) {
    //     char c = s[i];
    //     s[i] = s[j], s[j] = c;
    // }

    char* t = s;
    for(; *t != '\0'; t++)
        ;
    t--; // go back to last character

    for(; s < t; s++, t--) {
        char c = *s;
        *s = *t, *t = c;
    }
}

int main() {
    char s1[100];
    char* t1 = "Hello World";
    _strncpy(s1, t1, 8);
    printf("%s \n", s1);

    reverse(s1);
    printf("%s \n", s1);

    // the type void * (pointer to void) replaces char * as
    // the proper type for a generic pointer.

    // & - address of
    // The unary & operator only
    // applies to objects in memory: variables and array elements. It cannot be applied to
    // expressions, constants, or register variables.

    // * - dereference / indirection operator

    // postfix [] is evaluated before prefix &
    // ip = &z[0];

    /*
    // The syntax of the
    // declaration for a variable mimics the syntax of 
    // expressions in which the variable might appear.
    int *ip; // read as: expression *ip is an int
    // double *dp(char *); // read as: *dp has a value of double

    // all pointers are pointers to a specific data type (except void pointer)

    ++*ip; // increments what ip points to, associativity: right to left
    (*ip)++; // postfix has higher precedence than prefix
    */

    f1();

    char s[] = "hello";
    myfn(s);
    printf("%s\n", s);


    // int a[10];
    // the identifier of an array points to the zero-th element of the array
    // int* pa = &a;
    // int* pa = a; // same

    // In short, an array-and-index expression is equivalent to one written as a pointer and
    // offset.
    // int* ip;
    // p + i; // pointer to `i` elements beyond `p`
    // *(p + i)
    // p - i; // pointer to `i` elements before `p`

    // There is one difference between an array name and a pointer that must be kept in mind. A
    // pointer is a *variable*, so *pa=a and pa++ are legal*. But an array name is not a variable;
    // constructions like *a=pa and a++ are illegal*.

    // pass sub array by its starting index
    // f(&a[2]);
    // f(a+2);

    // If one is sure that the elements exist, it is also possible to index backwards in an array; p[-1],
    // p[-2], and so on are syntactically legal, and refer to the elements that immediately precede
    // p[0]. Of course, it is illegal to refer to objects that are not within the array bounds.

    // Any pointer can be
    // meaningfully compared for equality or inequality with zero. But the *behavior is undefined for
    // arithmetic or comparisons with pointers that do not point to members of the same array.*
    // (There is one exception: the address of the first element past the end of an array can be used in
    // pointer arithmetic.)

    // legal pointer operations
    // - assignment of pointers of the same type, 
    // - assign a pointer of one type to pointer of another type using a cast
    // - assigning a pointer of a type to void*
    // - adding or subtracting a pointer and an integer,
    // - subtracting or comparing two pointers to members of the same array,
    // - and assigning or comparing to zero.

    // a string constant is accessed by a pointer to its first element.

    char* pmessage = "now is the time"; // pointer to beginning of string constant is stored by pmessage
                                        // C does not provide operators to process an entire string of characters as a single unit

    // Individual characters within the array may be changed 
    // but amessage will always refer to the same storage.
    char amessage[] = "now is the time"; /* an array */

    // pmessage is a pointer, initialized to point to a string constant;
    // the pointer may subsequently be modified to point elsewhere, 
    // but the result is undefined if you try to modify the string contents.
    // char *pmessage = "now is the time"; /* a pointer */

    // char* s;
    // char* t;
    // s = t; // this just assigns pointer to s
    // strcpy(s, t); // copy string t to s

    // common way for pushing and popping from a stack
    // pointer p points to next free position on stack
    // *--p = val; // push val to stack
    // val = *--p; // pop top of stack into val

    // `a` is a two dimensional array with 200 int-sized locations allocated (on the stack)
    // elements can be accessed by a[i][j] or a[20*i + j]
    // storage used = 200 int sized locations
    int a[10][20];

    // array of 10 pointers allocated (allocated on the stack)
    // pointers are not initialized and must be explicitly initialized
    // if each of the 10 pointers pointed to an array of 20 ints each
    // then total storage used = 200 int sized locations + 10 pointers (array `b`) on the stack
    int *b[10];

    // The important advantage of the pointer array is that the rows of the array may be of
    // different lengths.
    

    return 0;
}