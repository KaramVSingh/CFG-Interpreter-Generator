#define SIZE 100
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// we want to define what a dictionary would look like
// we want to hash strings, store "datas"
// we insist that data is stored in the heap, otherwise undefined
// data types cannot be stored.

typedef struct Data {
    void *data;
    char **attributes;
    int n_attributes;
} Data;

typedef struct _Data {
    char *_name;
    struct _Data *next;
    Data* _data;
} _Data;

typedef struct HashMap {
    // we store 100 data pointers, hash will hash to 100
    _Data **data;
} HashMap;

HashMap* init(HashMap *h) {
    int i;
    h = (HashMap*)malloc(1 * sizeof(HashMap));
    h->data = (_Data**)malloc(SIZE * sizeof(_Data*));
    for(i = 0; i < SIZE; i++) {
        h->data[i] = NULL;
    }

    return h;
}

int hash_string(char* s) {
    int i = 0;
    int hash = 0;
    while(s[i] != '\0') {
        hash += (int)(s[i]) - (int)('a');
        i++;
    }

    return hash % SIZE;
}

Data* get(char* name, HashMap* map) {
    int h = hash_string(name);
    _Data* curr = map->data[h];

    while(curr) {
        if(!strcmp(curr->_name, name)) {
            return curr->_data;
        }
    }

    return NULL;
}

void set(char* name, Data* d, HashMap* map) {
    Data* n = get(name, map);
    if(n) {
        n->data = d->data;
        n->attributes = d->attributes;
        n->n_attributes = d->n_attributes;
    } else {
        _Data* new = (_Data*)malloc(1 * sizeof(_Data));
        new->_name = name;
        new->_data = d;
        new->next = NULL;

        _Data* curr = map->data[hash_string(name)];
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

int main() {
    HashMap *h;
    h = init(h);

    int x = 23;
    char *v[1];
    v[0] = "integer";
    Data* d = data_to_heap(&x, v, 1);

    set("karams integer", d, h);
    if(get("karams integer", h)) {
        int* r = get("karams integer", h)->data;
        printf("%d\n", *r);
    } else {
        printf("failed\n");
    }

    int y = 95;
    char *u[1];
    u[0] = "integer";
    Data* k = data_to_heap(&y, u, 1);

    set("karams integer", k, h);
    if(get("karams integer", h)) {
        int* r = get("karams integer", h)->data;
        printf("%d\n", *r);
    } else {
        printf("failed\n");
    }

}