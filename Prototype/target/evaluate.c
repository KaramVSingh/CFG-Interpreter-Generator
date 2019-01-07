#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "evaluate.h"

void set_hashmap(char *name, Data *d, HashMap *map) {
    Data* n = get_hashmap(name, map);
    if(n) {
        n->data = d->data; n->attributes = d->attributes; n->n_attributes = d->n_attributes;
    } else {
        _Data* new = (_Data*)malloc(1 * sizeof(_Data));
        new->_name = name;
        new->_data = d;
        new->next = NULL;

        _Data* curr = map->data[string_hashmap(name)];
        if(curr) {
            while(curr->next) {
                curr = curr->next;
            }
            curr->next = new;
        } else {
            map->data[string_hashmap(name)] = new;
        }
    }
}

int string_hashmap(char *s) {
    int i = 0;
    int hash = 0;
    while(s[i] != '\0') {
        hash += (int)(s[i]) - (int)('a');
        i++;
    }

    return hash % SIZE;
}

Data* get_hashmap(char *name, HashMap *map) {
    int h = string_hashmap(name);
    _Data* curr = map->data[h];

    while(curr) {
        if(!strcmp(curr->_name, name)) {
            return curr->_data;
        }
    }

    return NULL;
}

HashMap* init(HashMap *h) {
    int i;
    h = (HashMap*)malloc(1 * sizeof(HashMap));
    h->data = (_Data**)malloc(SIZE * sizeof(_Data*));
    for(i = 0; i < SIZE; i++) {
        h->data[i] = NULL;
    }

    return h;
}

Data** get_all_hashmap(HashMap *map, int *len, char ***names) {
    *len = 0;
    Data **d = (Data**)malloc(1 * sizeof(Data*));
    char **new_names = (char**)malloc(1 * sizeof(char*));
    int i;
    for(i = 0; i < SIZE; i++) {
        // for each index in map
        _Data* curr = map->data[i];
        while(curr != NULL) {
            *len = *len + 1;
            new_names = (char**)realloc(new_names, *len * sizeof(char*));
            d = (Data**)realloc(d, *len * sizeof(Data*));
            new_names[(*len) - 1] = curr->_name;
            d[(*len) - 1] = curr->_data;
            curr = curr->next;
        }
    }

    *names = new_names;
    return d;
}

Eval evaluate_help(Node *n, HashMap *env) {
void* REPLACEME;
}