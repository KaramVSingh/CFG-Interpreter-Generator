#if !defined(EVALUATE_H)
#define EVALUATE_H
#define SIZE 100

#include "parse.h"

typedef struct Data {
	void *data;
	int type;
	struct Data **args;
	int n_args;
	char **arg_names;
} Data;

typedef struct _Data {
    char *_name;
    struct _Data *next;
    Data *_data;
} _Data;

typedef struct HashMap {
    _Data **data;
} HashMap;

typedef struct Eval {
    HashMap *environment;
    Data *result;
} Eval;

HashMap* init(HashMap *h);
int string_hashmap(char *s);
Data* get_hashmap(char *name, HashMap *map);
void set_hashmap(char *name, Data *d, HashMap *map);
Data** get_all_hashmap(HashMap *map, int *len, char ***names);
Eval evaluate_help(Node *n, HashMap *env);

#endif