#include "tokenize.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    token_t *t = tokenize(argv[argc - 1]);
    while(t) {
        printf("%s\n", t->value);
        t = t->next;
    }
    
    return 0;
}