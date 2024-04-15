// Write a program entab that replaces strings of blanks by the minimum
// number of tabs and blanks to achieve the same spacing. Use the same tab stops as for detab.
// When either a tab or a single blank would suffice to reach a tab stop, which should be given
// preference

#include <stdio.h>

// including null terminator
#define MAX_LEN 1000

// returns length of string (excluding '\0')
int getline(char line[], int max_len) {
    char c;
    int i;

    for(i = 0; (c = getchar()) != EOF && c != '\n' && i < max_len-1; i++) {
        line[i] = c;
        if(c == '\n')
            break;
    }
    
    line[i] = '\0';

    return i;
}

int main() {
    int n = 4;
    int tab_len = 2;
    int len;
    char line[MAX_LEN];

    while((len = getline(line, MAX_LEN)) > 0) {
        int r = 1;
        char l2[MAX_LEN];
        int i2 = 0;

        for(int i = 0; i < len; i++) {
            if(line[i] == ' ') {
                int j;

                // skip through blanks
                for(j = i; line[j] == ' '; j++);

                // copy required number of blanks
                for(int k = 0; k < n-r; k++) {
                    l2[i2] = ' ';
                    i2++;
                }
                
                i = j-1;
                r = n;
            } else {
                l2[i2] = line[i];
                i2++;

                if(r < n) r++;
                else r = 1;
            }
        }

        l2[i2] = '\0';

        printf("%s\n", l2);
    }
}