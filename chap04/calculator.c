#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXOP 100 // maximum size of operand or operator
#define NUMBER '0' // signal that a number was found

#define MAXVAL 100 // maximum depth of val stack
#define BUFSIZE 100

int getop(char []);
void push(double);
double pop(void);

int getch(void);
void ungetch(int c);

int sp = 0; // next free stack position
double val[MAXVAL]; // value stack

// we could have used a single character for ungetch
// here we have used a buffer only to show a more general implementation
char buf[BUFSIZE];  // buffer for characters which we ungetch
int bufp = 0; // next free position in `buf`

// reverse polish calculator
int main() {
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

// push: push f onto value stack
void push(double f) {
    if(sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

// pop: pop and return top value from stack
double pop(void) {
    if(sp > 0)
        return val[--sp]; // note we just return the value, not overwrite with 0. it is automatically done with the next push
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

void print_top(void) {
    printf("top element: %f\n", val[sp-1]);
    printf("2nd from top element: %f\n", val[sp-2]);
}

void swap_top(void) {
    double tmp = val[sp-2];
    val[sp-2] = val[sp-1];
    val[sp-1] = tmp;
}

void clear_stack(void) {
    while(sp > 0) {
        val[sp] = 0.0;
        sp--;
    }

    val[sp] = 0.0; // clear 0th value
}

int getch(void) {
    // read all the characters from ungetch first
    // if empty then do getchar - from the stdio input buffer
    return (bufp > 0) ? buf[--bufp] : getchar(); // getchar gets character one by one from the input buffer, after enter / eof is sent. 
}

void ungetch(int c) {
    if(bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

// ungetch puts the pushed-back characters into a shared buffer -- a character array.
// getch reads from the buffer if there is anything else, and calls
// getchar if the buffer is empty.

// There must also be an index variable that records the position
// of the current character in the buffer.

int getop(char s[]) {
    int i, c;
    i = 0;

    while((s[0] = c = getch()) == ' ' || c == '\t') // skip whitespace
                                                    // store first non whitespace in s[0]
        ;

    s[1] = '\0';
    
    // maybe split string by whitespace?

    // check for minus sign
    // after that check if it is a letter
        // check for more letters - if whitespace - then it is a variable
        // if more letters - could be function
            // if satisfies valid function name, take it as the operand
            // check in main() if the number of operands match our function
    // if we have a variable, get its value from the calculator variable storage array, and return its type as NUMBER (pushed to stack in main() - and return from getop() immediately (and cleanly)

    if(!isdigit(c) && c != '.') {
        // implement negative numbers
        if(c == '-') {
            int c2 = getch();
            
            if(c2 == ' ' || c2 == '\t')
                return c;
            
            s[1] = c = c2; // assign digit to c
            i = 1;
        } else {
            return c;
        }
    }

    if(isdigit(c)) // collect integer part
        while(isdigit(s[++i] = c = getch()));
    
    if(c == '.') // collect decimal part
        while(isdigit(s[++i] = c = getch()));

    s[i] = '\0';

    if(c != EOF)
        ungetch(c);

    return NUMBER;
}