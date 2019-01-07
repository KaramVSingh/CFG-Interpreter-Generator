#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include "tokenize.h"

// https://stackoverflow.com/questions/1631450/c-regular-expression-howto
Match* match(const char *string, char *pattern) {
    int status;
    regmatch_t* details = (regmatch_t*)malloc(1 * sizeof(regmatch_t));
    regex_t re;

    if(regcomp(&re, pattern, REG_EXTENDED) != 0) {
        return NULL;
    }

    status = regexec(&re, string, (size_t) 1, details, 0);
    regfree(&re);
    if(status != 0) {
        return NULL;
    }

    Match *m = (Match*)malloc(1 * sizeof(Match));
    m->start = details[0].rm_so;
    m->end = details[0].rm_eo;

    return m;
}

Token* apply_tokens(char *curr) {
    // all_tokens is a list of regular expressions. index number is how we will name each token type
    // all_tokens should be sorted as [ literal tokens ] [ regexp tokens ] where literal tokens
    // is sorted by length as longest to shortest. each regex should be preceded by a carrat
    char* all_tokens[8] = {"^>>", "^>=", "^<<", "^<=", "^<", "^>", "^[0-9]+", "^[a-z]+"};
    int num_toks = 8;
    Token* head = NULL;
    Token* curr_tok = NULL;
    Match* m;

    while(curr[0] != '\0') {
        int i, found = 0;
        for(i = 0; i < num_toks; i++) {
            if((m = match(curr, all_tokens[i]))) {
                Token *t = (Token*)malloc(1 * sizeof(Token));
                t->type = i;
                char* n_s = malloc((m->end + 1) * sizeof(char));
                strncpy(n_s, curr, m->end);
                n_s[m->end] = '\0';
                t->value = n_s;
                t->next = NULL;
                if(head == NULL) {
                    head = t;
                    curr_tok = t;
                } else {
                    curr_tok->next = t;
                    curr_tok = curr_tok->next;
                }
                curr += m->end;
                found = 1;
                break;
            }
        }

        if(!found) {
            printf("Unrecognized Token: %s.\n", curr);
            exit(0);
        }
    }

    return head;
}

// this function takes a file and splits it into its prospective tokens
Token* tokenize(char *filename) {
    FILE* fp = fopen(filename, "r");
    if(fp == NULL) {
        printf("Tokenizer Error: File not found\n");
    }
    int curr_size = 0;
    char *curr = (char*)malloc(1 * sizeof(char));
    curr[curr_size] = '\0';
    Token *head = NULL;
    Token *curr_tok = NULL;
    char c;

    while((c = fgetc(fp)) != EOF) {
        if(c == ' ' || c == '\t' || c == '\n' || c == '\r') {
            Token *t = apply_tokens(curr);
            if(head == NULL) {
                head = t;
                curr_tok = t;
            } else {
                curr_tok->next = t;
            }
            while(curr_tok->next != NULL) {
                curr_tok = curr_tok->next;
            }

            curr_size = 0;
            curr = (char*)malloc(1 * sizeof(char));
            curr[curr_size] = '\0';
        } else {
            curr_size++;
            curr = (char*)realloc(curr, (curr_size + 1) * sizeof(char));
            curr[curr_size] = '\0';
            curr[curr_size - 1] = c;
        }
    }

    if(curr_size != 0) {
        Token *t = apply_tokens(curr);
        if(head == NULL) {
            head = t;
            curr_tok = t;
        } else {
            curr_tok->next = t;
        }
    }

    fclose(fp);

    return head;
}