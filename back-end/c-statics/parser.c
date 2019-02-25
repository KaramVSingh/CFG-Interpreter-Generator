#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

node_t* parse_clean(node_t *n) {
    if(n->n_next == 1 && n->n_tokens == 0) {
        return parse_clean(n->next[0]);
    } else {
        int i;
        for(i = 0; i < n->n_next; i++) {
            n->next[i] = parse_clean(n->next[i]);
        }

        return n;
    }
}

node_t* parse(token_t *h) {
    return parse_clean(NULL);
}

void s_move(char *dest, char *src) {
    int i = 0;
    while(src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = src[i];
}

int lookahead(token_t *h) {
    return (h != NULL? h->index : -1);
}

token_t* match_token(token_t *h, int v) {
    if(lookahead(h) == v) {
        return h->next;
    } else {
        printf("Parse Error: Unexpected token -> %s\n", h->value);
        exit(0);
    }

    return NULL;
}


