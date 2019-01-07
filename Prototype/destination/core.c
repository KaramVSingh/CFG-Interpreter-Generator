#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokenize.h"
#include "parse.h"
#include "evaluate.h"

void printast(Node *n, int depth) {
    printf("depth: %d, name: %s -> ", depth, n->name);
    int i;
    for(i = 0; i < n->n_tokens; i++) {
        printf("%s ", n->tokens[i]);
    }
    printf("\n");
    for(i = 0; i < n->n_next; i++) {
        printast(n->next[i], depth + 1);
    }
}

int main(int argc, char *argv[]) {
    Token* h = tokenize(argv[argc - 1]);
    Node* n = parse(h);
    HashMap *env;
    env = init(env);
    Eval e = evaluate_help(n, env);
}