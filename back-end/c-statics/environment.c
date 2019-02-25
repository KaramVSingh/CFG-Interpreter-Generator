#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "environment.h"

_data_t *get_from_environment_unsafe(char *name, environment_t *map) {
    int h = hash_string(name);
    _data_t* curr = map->data[h];

    while(curr) {
        if(!strcmp(curr->_name, name)) {
            return curr;
        }
    }

    return NULL;
}

void set_in_environment(char *name, data_t *d, environment_t *map) {
    // this returns the _data_t
    _data_t* n = get_from_environment_unsafe(name, map);

    if(n) {
        n->_data = d;
    } else {
        _data_t* new = (_data_t*)malloc(1 * sizeof(_data_t));
        new->_name = name;
        new->_data = d;
        new->next = NULL;

        _data_t* curr = map->data[hash_string(name)];

        if(curr) {
            while(curr->next) {
                curr = curr->next;
            }
            curr->next = new;
        } else {
            map->data[hash_string(name)] = new;
        }
    }
}

int hash_string(char *s) {
    int i = 0;
    int hash = 0;
    while(s[i] != '\0') {
        hash += (int)(s[i]) - (int)('a');
        i++;
    }

    return hash % SIZE;
}

data_t* get_from_environment(char *name, environment_t *map) {
    int h = hash_string(name);
    _data_t* curr = map->data[h];

    while(curr) {
        if(!strcmp(curr->_name, name)) {
            return curr->_data;
        }
    }

    return NULL;
}

environment_t* init(environment_t *h) {
    int i;
    h = (environment_t*)malloc(1 * sizeof(environment_t));
    h->data = (_data_t**)malloc(SIZE * sizeof(_data_t*));
    for(i = 0; i < SIZE; i++) {
        h->data[i] = NULL;
    }

    return h;
}

data_t** get_all_environment(environment_t *map, int *len, char ***names) {
    *len = 0;
    data_t **d = (data_t**)malloc(1 * sizeof(data_t*));
    char **new_names = (char**)malloc(1 * sizeof(char*));
    int i;
    for(i = 0; i < SIZE; i++) {
        // for each index in map
        _data_t* curr = map->data[i];
        while(curr != NULL) {
            *len = *len + 1;
            new_names = (char**)realloc(new_names, *len * sizeof(char*));
            d = (data_t**)realloc(d, * len * sizeof(data_t*));
            new_names[(*len) - 1] = curr->_name;
            d[(*len) - 1] = curr->_data;
            curr = curr->next;
        }
    }

    *names = new_names;
    return d;
}