#if !defined(EVALUATE_H)
#define EVALUATE_H
#define SIZE 100

#include "parser.h"
#include "environment.h"

typedef struct eval_t {
    environment_t *environment;
    data_t *result;
} eval_t;

eval_t evaluate(node_t *n, environment_t *env);

#endif