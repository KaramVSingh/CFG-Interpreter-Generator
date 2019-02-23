#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if(argc != 2) {
        printf("Must specify file as argument.\n");
        return 1;
    }

    token_t *t = tokenize(argv[argc - 1]);
    while(t) {
        printf("%s\n", t->value);
        t = t->next;
    }
    
    return 0;
}