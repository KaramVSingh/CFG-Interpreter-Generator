#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>

// Karam Singh: 1/7/2019

// for proper usage of tokenizer:
// patterns prepopulated in must be sorted by priority. this means that tokens
// will be sorted by length with the exception of variable length tokens which will be placed last
// we assume no whitespace tokens (this is a whitespace ignoring tokenizer)

// this function:
// args -> ()
// retn -> tokenset_t* = complied regexes
tokenset_t* init_tokens() {
    tokenset_t *tokenset = (tokenset_t*)malloc(1 * sizeof(tokenset_t));
    char *patterns[11] = {"<<", ">>", "<=", ">=", "<", ">", "=", "'", "[0-9]+", "[0-9]+\.[0-9]*", "[a-zA-Z]+"};
    int is_delimiting[11] = { 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 };
    int n_tokens = 11;

    tokenset->n_tokens = n_tokens;
    tokenset->right_search = (regex_t**)malloc(n_tokens * sizeof(regex_t*));
    tokenset->left_search = (regex_t**)malloc(n_tokens * sizeof(regex_t*));
    tokenset->is_delimiting = (int*)malloc(n_tokens * sizeof(int));    

    int i;
    for(i = 0; i < n_tokens; i++) {
        tokenset->is_delimiting[i] = is_delimiting[i];
        tokenset->right_search[i] = (regex_t*)malloc(1 * sizeof(regex_t));
        tokenset->left_search[i] = (regex_t*)malloc(1 * sizeof(regex_t));

        char *malleable = (char*)malloc((strlen(patterns[i]) + 2) * sizeof(char));
        malleable[0] = '^';
        malleable[1] = '\0';
        malleable = strcat(malleable, patterns[i]);
        if(regcomp(tokenset->left_search[i], malleable, REG_EXTENDED)) {
            printf("Tokenizer Error -> unable to compile regular expression %s.\n", malleable);
            exit(1);
        }

        malleable[0] = '\0';
        malleable = strcat(malleable, patterns[i]);
        malleable[strlen(patterns[i])] = '$';
        malleable[strlen(patterns[i]) + 1] = '\0';
        if(regcomp(tokenset->right_search[i], malleable, REG_EXTENDED)) {
            printf("Tokenizer Error -> unable to compile regular expression %s.\n", malleable);
            exit(1);
        }
    }

    return tokenset;
}

// this function:
// args -> char *string = string to be matched
//      -> tokenset_t *set = set of regular expressions
//      -> int is_left = operation type
// retn -> match_t * = data from match
match_t* match_with_token(char *string, tokenset_t *tokenset, int is_left) {
    regmatch_t* details = (regmatch_t*)malloc(1 * sizeof(regmatch_t));

    int i;
    for(i = 0; i < tokenset->n_tokens; i++) {
        regex_t *r;
        if(is_left) {
            r = tokenset->left_search[i];
        } else if(tokenset->is_delimiting[i]) {
            r = tokenset->right_search[i];
        } else {
            continue;
        }

        if(!regexec(r, string, (size_t) 1, details, 0)) {
            // we have a match
            match_t *m = (match_t*)malloc(1 * sizeof(match_t));
            m->index = i;
            m->is_delimiting = tokenset->is_delimiting[i];
            m->start = details[0].rm_so;
            m->end = details[0].rm_eo;
            free(details);
            m->value = (char*)malloc((m->end - m->start + 1) * sizeof(char));

            int j;
            for(j = m->start; j < m->end - m->start; j++) {
                m->value[j - m->start] = string[j];
            }

            m->value[j] = '\0';
            return m;
        }
    }

    free(details);
    return NULL;
}

// this function:
// args -> tokenset_t* = compiled regexes
// retn -> () = frees regexes
void delete_tokens(tokenset_t *tokenset) {
    int i;
    for(i = 0; i < tokenset->n_tokens; i++) {
        regfree(tokenset->left_search[i]);
        regfree(tokenset->right_search[i]);
    }

    free(tokenset->left_search);
    free(tokenset->right_search);
    free(tokenset->is_delimiting);
    free(tokenset);
}

// this function:
// args -> char *filename = file to be tokenized
// retn -> token_t* = linked list which contains all the tokens
token_t* tokenize(char *filename) {
    FILE *fp = fopen(filename, "r");

    if(fp == NULL) {
        printf("Tokenizer Error: %s not found.\n", filename);
        exit(1);
    }

    char c;
    char *curr = (char*)malloc(1 * sizeof(char));
    int curr_len = 0;
    curr[0] = '\0';
    tokenset_t *tokenset = init_tokens();
    token_t *head = NULL;
    token_t *current_token = NULL;

    while(1) {
        c = fgetc(fp);
        // for each character in the file
        if(c == EOF || c == '\t' || c == '\n' || c == ' ' || c == '\r') {
            char *curr_holder = curr;
            while(curr_len != 0) {
                // we want to shrink it until we have matched all the tokens
                match_t *m = match_with_token(curr, tokenset, 1);
                if(!m) {
                    // this is an unfarmiliar token
                    printf("Tokenize Error -> Unexpected token %s.\n", curr);
                    exit(1);
                }

                token_t *new_token = (token_t*)malloc(1 * sizeof(token_t));
                new_token->index = m->index;
                new_token->type = m->is_delimiting;
                new_token->value = m->value;
                new_token->next = NULL;

                curr_len -= (m->end - m->start);
                curr += (m->end - m->start);

                if(new_token->type) {
                    // we want to get all the characters until we meet the other delimiter
                    // we do not care about any other value until we get to the similar delimiter
                    int found = 0;

                    while(curr_len != 0) {
                        int slen = strlen(new_token->value) + 2;
                        new_token->value = (char*)realloc(new_token->value, slen * sizeof(char));
                        new_token->value[slen - 2] = curr[0];
                        new_token->value[slen - 1] = '\0';

                        curr++;
                        curr_len -= 1;

                        match_t *del_m = match_with_token(new_token->value, tokenset, 0);
                        if(del_m) {
                            if(del_m->index == new_token->index) {
                                found = 1;
                                free(del_m);
                                break;
                            }

                            free(del_m);
                        }
                    }

                    if(!found) {
                        while(1) {
                            int slen = strlen(new_token->value) + 2;
                            new_token->value = (char*)realloc(new_token->value, slen * sizeof(char));
                            new_token->value[slen - 2] = c;
                            new_token->value[slen - 1] = '\0';

                            match_t *del_m = match_with_token(new_token->value, tokenset, 0);
                            if(del_m) {
                                if(del_m->index == new_token->index) {
                                    found = 1;
                                    free(del_m);
                                    break;
                                }

                                free(del_m);
                            }

                            c = fgetc(fp);
                            if(c == EOF) {
                                printf("Tokenize Error -> delimited token not matched\n");
                                exit(1);
                            }
                        }
                    }
                }

                if(!head) {
                    head = new_token;
                    current_token = new_token;
                } else {
                    current_token->next = new_token;
                    current_token = current_token->next;
                }

                free(m);
            }
            
            curr = (char*)realloc(curr_holder, 1 * sizeof(char));
            curr_len = 0;
            curr[0] = '\0';

            if(c == EOF) {
                break;
            }
        } else {
            curr_len++;
            curr = (char*)realloc(curr, (curr_len + 1) * sizeof(char));
            curr[curr_len] = '\0';
            curr[curr_len - 1] = c;
        }
    }

    fclose(fp);
    free(curr);
    delete_tokens(tokenset);
    return head;
}