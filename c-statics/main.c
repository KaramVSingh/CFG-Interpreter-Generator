#include "lexer.h"
#include "parser.h"
#include "evaluator.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if(argc != 2) {
        printf("Must specify file as argument.\n");
        return 1;
    }
    
    token_t *t = tokenize(argv[argc - 1]);

    /*
    while(t) {
        printf("%s\n", t->value);
        t = t->next;
    }
    */

    node_t* n = parse(t);
    environment_t *env;
    env = init(env);
    eval_t e = evaluate(n, env);
    
    return 0;
}