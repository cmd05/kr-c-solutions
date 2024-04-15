#include <stdio.h>

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

    // i and j point one beyond end null-terminator at the end of while
    // but they are not used further
}

int main() {
    // data types: char, int, float, double
    // qualifiers: short and long

    // sizeof(short) <= sizeof(int) <= sizeof(long)
    // printable chars are always positive

    long l1 = 123456789L;
    unsigned int ui1 = 1234567U;
    unsigned long ul1 = 123456789UL;

    // floating points are double by default

    // 1.2f // float type
    // 245.55L // long double
    // 0xFL // long int
    // 0xFUL // unsigned long int

    // an arbitrary byte-sized bit pattern can be specified by
    // '\ooo'
    // where ooo is one to three octal digits (0...7) or by
    // '\xhh'
    // where hh is one or more hexadecimal digits (0...9, a...f, A...F).

    char line[] = "hello "
                  "world";

    printf(line);

    enum escapes { BELL = '\a', BACKSPACE = '\b', TAB = '\t',
        NEWLINE = '\n', VTAB = '\v', RETURN = '\r' };
    enum months { JAN = 1, FEB, MAR, APR, MAY, JUN,
        JUL, AUG, SEP, OCT, NOV, DEC };
    /* FEB = 2, MAR = 3, etc. */

    int year = 2000;
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
        printf("%d is a leap year\n", year);
    else
        printf("%d is not a leap year\n", year);

    // External and static variables are initialized to
    // zero by default. Automatic variables for which is no explicit initializer have undefined (i.e.,
    // garbage) values

    // precedence of != is higher than assignment,
    // parentheses are needed in
    // (c=getchar()) != '\n'

    // exercise 2
    // int i = 0;
    // while((c = getchar()) != '\n') {
    //     if(i >= lim-1)
    //         break
    //     if(c == EOF)
    //         break
        
    //     s[i] = c;
    //     i++;
    // }

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

    // bitwise operations
    // The bitwise AND operator & is often used to mask off some set of bits, 
    // The bitwise OR operator | is used to turn bits on:

      if(1)
        if(0)
          printf("a");
      else // this is associated with the nested if block (use braces for proper association)
        printf("b");
}