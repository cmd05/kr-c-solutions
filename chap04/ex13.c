#include <stdio.h>
#include <string.h>

void reverse_base(char s[], int i) {
    int len = strlen(s);
    if(len < 2)
        return;

    if(i < (len / 2 - 1))
        reverse_base(s, i+1);
    
    char tmp = s[i];
    s[i] = s[len - i - 1];
    s[len - i - 1] = tmp;
}

void reverse(char s[]) {
    reverse_base(s, 0);
}

int main() {
    char s[] = "race";
    reverse(s);
    printf("%s", s);
}