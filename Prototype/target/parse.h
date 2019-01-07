#if !defined(PARSE_H)
#define PARSE_H

#include "tokenize.h"

typedef struct Node {
    char *name;                     // name of node instruction (identifier)
    char **tokens;                  // tokens captured by node
    int n_tokens;                   // number of tokens captured by node
    struct Node **next;             // children of node in AST
    int n_next;                     // number of children in node
} Node;

typedef struct Tuple {
    Node *node;
    Token *token;
} Tuple;

int lookahead(Token *h);
Token* match_token(Token *h, int v);
Node* parse(Token *h);


#endif