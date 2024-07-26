#include <stdio.h>
#include <stdlib.h>
#include "calc.h"

#define MAXOP 100 // maximum size of operand or operator

extern void some_function();

// reverse polish calculator
int main() {
    some_function();

    int type; // type of the operand / operator
    double op2; // temporary variable to store operand
    char s[MAXOP]; // string to store operand / operation

    while((type = getop(s)) != EOF) {
        switch(type) {
        case NUMBER:
            push(atof(s)); // push number to stack
            break;
        case '+':
            push(pop() + pop());
            break;
        case '*':
            push(pop() * pop());
            break;
        case '-':
            // the order in which the two calls of pop are evaluated is not defined. To guarantee the right
            // order, it is necessary to pop the first value into a temporary variable as we did
            // + and * are commutative so we don't need to distinguish the operands,
            // but we need to for - and /
            op2 = pop(); // distinguish the right operand
            push(pop() - op2);
            break;
        case '%':
            op2 = pop(); // distinguish the right operand
            push((double) ((int) (pop()) % (int) (op2)));
            break;
        case '/':
            op2 = pop();
            if(op2 != 0.0)
                push(pop() / op2);
            else
                printf("error: zero divisor\n");
            break;
        case 'c':
            clear_stack();
            break;
        case '@':
            print_top();
            break;
        case '$':
            swap_top();
            break;
        case '\n':
            printf("\t%.8g\n", pop()); // print the result
            break;
        default:
            printf("error: unknown command %s\n", s);
            break;
        }
    }

    return 0;
}