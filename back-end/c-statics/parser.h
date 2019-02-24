#if !defined(PARSE_H)
#define PARSE_H

#include "lexer.h"

typedef struct node_t {
    char *name;                     // name of node instruction (identifier)
    char **tokens;                  // tokens captured by node
    int n_tokens;                   // number of tokens captured by node
    struct node_t **next;           // children of node in AST
    int n_next;                     // number of children in node
} node_t;

typedef struct tuple_t {
    node_t *node;
    token_t *token;
} tuple_t;

int lookahead(token_t *h);
token_t* match_token(token_t *h, int v);
node_t* parse(token_t *h);



#endif