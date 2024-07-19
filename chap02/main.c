#include <stdio.h>

// the standard library strlen(), returns the length
// of the string **excluding** the null terminator character
// int strlen(char s[]) {
//     int i;

//     while(s[i] != '\0')
//         i++;
    
//     return i;
// }

int isOdd(int i) {
    return i&1; // returns 0 or 1
}

int atoi(char s[]) {
    int n = 0;

    for(int i = 0; s[i] >= '0' && s[i] <= '9'; i++)
        n = n*10 + (s[i] - '0');
    
    return n;
}

/* squeeze: delete all c from s */
void squeeze(char s[], int c)
{
    int i, j;
    for (i = j = 0; s[i] != '\0'; i++)
        if (s[i] != c)
            s[j++] = s[i];
    s[j] = '\0';

    // compact form of:
    // if (s[i] != c) {
    //     s[j] = s[i];
    //     j++;
    // }
}

void strcat(char* s, char* t) {
    int i, j;
    i = j = 0;

    for(; s[i] != '\0'; i++); // go to end of s

    while((s[i++] = t[j++]) != '\0'); // copy t
    // here the null-terminator from `t` is also copied to `s` 
    // as the comparison operation happens after assignemtn

    // i and j point one beyond end null-terminator at the end of while
    // but they are not used further
}

// char lower(char c) {
//     if(c >= 'A' || c <= 'Z')
//         return c + ('a' - 'A');
//     else
//         return c;
// }

char lower(char c) {
    return (c >= 'A' || c <= 'Z') ? (c + ('a' - 'A')) : c;
}

// getbits: get n bits from position p
unsigned getbits(unsigned x, int p, int n) {
    // right shift positions from [p, p-n] to rightmost place
    // and then extract those bits
    return (x >> ((p + 1) - n)) & ~(~0 << n);
}

int main() {
    // data types: char, int, float, double
    // qualifiers: short and long

    // sizeof(short) <= sizeof(int) <= sizeof(long)
    // printable chars are always positive

    long l1 = 123456789L; // long
    unsigned int ui1 = 1234567U; // unsigned
    unsigned long ul1 = 123456789UL; // unsigned long

    // floating points are double by default
    // 2.566 // double by default

    // 1.2f // float type
    // 245.55L // long double
    // 31 (dec), 037 (oct), 0x1f (hex)
    // 0xFL // long int (15L)
    // 0xFUL // unsigned long int (15UL)

    // an arbitrary byte-sized bit pattern can be specified by
    // '\ooo'
    // where ooo is one to three octal digits (0...7) or by
    // '\xhh'
    // where hh is one or more hexadecimal digits (0...9, a...f, A...F).

    // octal representation
    // #define VTAB '\013' // ascii vertical tab
    // #define BELL '\007' // ascii bell character

    // // hex representation
    // #define VTAB '\xb' // ascii vertical tab
    // #define BELL '\x7'  // ascii bell character

    // string constant / string literal / C string
    // "this is a string"
    // "" // empty string
    // string const

    // NOTE:
    // 'x' // character constant
    // "x" // string with single character and null terminator
    
    char line[] = "hello " "world"; // same as "hello world"
    char line2[] = "hello " 
                  "world"; // same as "hello world"

    // printf(line);

    enum escapes { BELL = '\a', BACKSPACE = '\b', TAB = '\t',
        NEWLINE = '\n', VTAB = '\v', RETURN = '\r' };
    enum months { JAN = 1, FEB, MAR, APR, MAY, JUN,
        JUL, AUG, SEP, OCT, NOV, DEC };
    /* FEB = 2, MAR = 3, etc. */

    enum test { car, bike = 2, scooter, truck, van = 0, plane};
    // enum test2 { apple, banana, orange, bike }; // error: redeclaration of enumerator 'bike'
    // enum test t = truck;

    printf("%d %d\n", car, van);

    printf("(-5)/2=%d\n", (-5 / 2));
    printf("(-5)%%2=%d\n", (-5 % 2));

    // int year = 2000;
    // if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
    //     printf("%d is a leap year\n", year);
    // else
    //     printf("%d is not a leap year\n", year);

    // External and static variables are initialized to
    // zero by default. Automatic variables for which is no explicit initializer have undefined (i.e.,
    // garbage) values

    // precedence of != is higher than assignment,
    // parentheses are needed in
    // (c=getchar()) != '\n'

    // narrow to wide: legal and automatic
    // wide to narrow: legal (but warning)
    // invalid expression: ex: subscripting array with float - error

    // If there are no unsigned
    // operands, however, the following informal set of rules will suffice:
    // • If either operand is long double, convert the other to long double.
    // • Otherwise, if either operand is double, convert the other to double.
    // • Otherwise, if either operand is float, convert the other to float.
    // • Otherwise, convert char and short to int.
    // • Then, if either operand is long, convert the other to long.

    int i;
    char c;

    i = c;
    c = i; // higher order bits of `i` are dropped. hence, c retains its value

    float x = (float) (5 + 5); // cast operator

    // bitwise operations
    // The bitwise AND operator & is often used to mask off some set of bits, 
    // The bitwise OR operator | is used to turn bits on:

    // automatic type coercion
    double root2 = sqrt(2); // integer 2 is coerced into double value 2.0 without a cast
                            // , given the function prototype `double sqrt(double)`


    printf("\n");
    if(1)
        if(0)
            printf("a");
    else // this is associated with the nested if block (use braces for proper association)
        printf("b");
}