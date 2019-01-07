#if !defined(TOKENIZE_H)
#define TOKENIZE_H

typedef struct Token {
    int type;
    char *value;
    struct Token *next;
} Token;

typedef struct Match {
    int start;
    int end;
} Match;

Match* match(const char *string, char *pattern);
Token* apply_tokens(char *curr);
Token* tokenize(char *filename);

#endif