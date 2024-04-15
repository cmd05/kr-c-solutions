#include <stdio.h>

// function prototype
int power(int base, int n);

// function defintion
int power(int base, int n) {
    for(; n > 1; n--)
        base *= base;
    
    return base;
}

/* print Fahrenheit-Celsius table
for fahr = 0, 20, ..., 300 */
int main()
{
    // float fahr, celsius;
    // float lower, upper, step;
    // lower = 0; /* lower limit of temperature scale */
    // upper = 300; /* upper limit */
    // step = 20; /* step size */
    // fahr = lower;
    // while (fahr <= upper) {
    //     celsius = 5 * (fahr-32) / 9;
    //     // printf("%d\t%d\n", fahr, celsius);
    //     // %6 - atleast 6 characteres wide
    //     printf("%-3.1f %6.1f\n", fahr, celsius); // right justified
    //     // printf("%-3.1f %.2f\n", fahr, celsius); // right justified
    //     fahr = fahr + step;
    // }

    // float x = 5/9 * 10; // 0
    // float x = 5/9.0 * 10; // 5.55

    /* %d vs %i */
    // These are identical for printf but different for scanf.
    // For printf, both %d and %i designate a signed decimal integer. 
    // For scanf, %d and %i also means a signed integer but %i inteprets the input as a hexadecimal number
    // if preceded by 0x and octal if preceded by 0 and otherwise interprets the input as decimal.

    // printf("%d %% %d == %d", 10, 4, 10%4);

    // int i = 0;
    // for(printf("x"); i < 100; i++, printf("hi"));

    // char c = getchar();
    // while(c != EOF) { // eof is -1, which char can hold
    //     putchar(c);
    //     c = getchar();
    // }

    // while ((c = getchar()) != EOF)
    //     putchar(c);

    // long nc;
    // nc = 0;
    // while (getchar() != EOF)
    //     ++nc;
    // printf("%ld\n", nc);

    // printf("%d", EOF);

    // double nc;
    // for (nc = 0; getchar() != EOF; ++nc);
    // printf("%.0f\n", nc);

    char c = 0;
    if((c = 220) == 220) // RHS of `==` is compared with `value assigned to variable after assignment` 
        printf("equal");
    else
        printf("%d", (int) c); // 220 overflows to -36
}