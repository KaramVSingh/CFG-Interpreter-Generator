#if !defined(LEXER_H)
#define LEXER_H

#include <regex.h>
#include <string.h>

// this is the token which will be returned after processing
typedef struct token_t {
    int index;
    int type;
    char *value;
    struct token_t *next;
} token_t;

// this is the empty token which will be initialized with regexes
typedef struct tokenset_t {
    // contains a list of regexes to be analyzed
    // contains an array which indicates which indexes in the regexes are delimiting
    // arrays should be sorted by token length
    regex_t **right_search;
    regex_t **left_search;
    int *is_delimiting;
    int n_tokens;
} tokenset_t;

typedef struct match_t {
    int index;
    int is_delimiting;
    int start;
    int end;
    char *value;
} match_t;

token_t* tokenize(char *filename);

#endif