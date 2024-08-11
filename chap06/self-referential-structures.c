#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100
struct tnode* addtree(struct tnode*, char*, unsigned int* nnodes);
void treeprint(struct tnode*);
void treeprint_sorted(struct tnode*, unsigned int n);
int getword(char*, int, FILE* file);

struct tnode* talloc(void);
char* my_strdup(char*);

// tree node
struct tnode {
    char* word; // points to next word
    unsigned int count;  // number of occurences
    // structure can contain pointers to structures of the same type
    // but not their instances
    struct tnode* left;
    struct tnode* right;
};

// for sorting
struct Word {
    char* word;
    unsigned int count;
};

int main() {
    struct tnode* root;
    char word[MAXWORD];
    unsigned int nnodes = 0;

    root = NULL;
    FILE* fp = fopen("words.txt", "r");

    if (!fp) {
        fprintf(stderr, "File opening failed");
        return -1;
    }

    while(getword(word, MAXWORD, fp) != EOF)
        if(isalpha(word[0]))
            root = addtree(root, word, &nnodes);
        
    // printf("%d\n", nnodes);    
    // treeprint(root);
    treeprint_sorted(root, nnodes);
    return 0;
}

// addtree: add a node with w, at or below p
struct tnode* addtree(struct tnode* p, char* w, unsigned int* nnodes) {
    int cond;

    if(p == NULL) { // a new word has arrived
        p = talloc(); // create a new node
        p->word = my_strdup(w);
        p->count =  1;
        p->left = p->right = NULL; // initialize left and right nodes of new node to NULL

        (*nnodes)++;
    } else if ((cond = strcmp(w, p->word)) == 0)
        p->count++; // repeated word
    else if(cond < 0) // less than condition - left subtree
        p->left = addtree(p->left, w, nnodes);
    else // right subtree
        p->right = addtree(p->right, w, nnodes);

    return p; // return pointer to `w` in tree
}

void treeprint(struct tnode* p) {
    if(p != NULL) {
        treeprint(p->left);
        printf("%4d %s\n", p->count, p->word);
        treeprint(p->right);
    }
}

void treeprint_sorted_base(struct tnode* p, struct Word* words) {
    static int i = 0;

    if(p != NULL) {
        treeprint_sorted_base(p->left, words);
        
        words[i].word = p->word;
        words[i].count = p->count;

        i++;
        
        treeprint_sorted_base(p->right, words);
    }
}

int Word_cmp(const void* a, const void* b) {
    unsigned int diff = ((struct Word*) a)->count - ((struct Word*) b)->count;
    diff *= -1; // reverse sorting on count

    if(diff == 0)
        return strcmp(((struct Word*) a)->word, ((struct Word*) b)->word); // sort alphabetically if count is equal
    
    return diff;
}

void treeprint_sorted(struct tnode* p, unsigned int n) {
    struct Word* words = malloc(n * sizeof(struct Word));
    treeprint_sorted_base(p, words);

    qsort(words, n, sizeof(struct Word), Word_cmp);

    for(struct Word* p2 = words; p2 < words + n; p2++)
        printf("%4d %s\n", p2->count, p2->word);
}

struct tnode* talloc(void)
{
    return (struct tnode*) malloc(sizeof(struct tnode));
};

char* my_strdup(char* s) { // make a duplicate of s
    char* p = (char*) malloc(strlen(s) + 1); // include space for null-terminator also

    if(p != NULL)
        strcpy(p, s);

    return p;
}

int getword(char* word, int lim, FILE* file) {
    int c;
    char* w = word;

    while(isspace(c = getc(file)))
        ;
    
    if(c != EOF)
        *w++ = c;
    
    if(!isalpha(c)) {
        *w = '\0';
        return c; // returns non-alphabetic character (can be EOF)
    }

    for(; --lim > 0; w++)
        if(!isalnum(*w = getc(file))) {
            ungetc(*w, file); // return non alphanumeric character to input buffer
            break;
        }
    
    *w = '\0';
    
    // printf("%s\n", word);

    return word[0];
}