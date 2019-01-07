#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "evaluate.h"

void set_hashmap(char *name, Data *d, HashMap *map) {
    Data* n = get_hashmap(name, map);
    if(n) {
		n->data = d->data;
		n->type = d->type;
		n->args = d->args;
		n->n_args = d->n_args;
		n->arg_names = d->arg_names;
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
	if(!strcmp(n->name, "EQOPERATOR")) {
	    // 0: !=, 1: ==
	    int *v1 = (int*)malloc(1 * sizeof(int));
	    char **v2 = NULL;
	    Data *v3 = (Data*)malloc(1 * sizeof(Data));
	    Eval v4;
	    v3->data = v1;
	    v3->type = -1;
	    v4.environment = env;
	    v4.result = v3;
	
	    if(!strcmp(n->tokens[0], "==")) {
	        *v1 = 1;
	    } else {
	        *v1 = 0;
	    }
	
	    return v4;
	} else if(!strcmp(n->name, "REOPERATOR")) {
	    // 0: <, 1: > 2: <= 3: >=
	    int *v1 = (int*)malloc(1 * sizeof(int));
	    char **v2 = NULL;
	    Data *v3 = (Data*)malloc(1 * sizeof(Data));
	    Eval v4;
	    v3->data = v1;
	    v3->type = -1;
	    v4.environment = env;
	    v4.result = v3;
	
	    if(!strcmp(n->tokens[0], "<")) {
	        *v1 = 0;
	    } else if(!strcmp(n->tokens[0], ">")) {
	        *v1 = 1;
	    } else if(!strcmp(n->tokens[0], "<=")) {
	        *v1 = 2;
	    } else if(!strcmp(n->tokens[0], ">=")) {
	        *v1 = 3;
	    }
	
	    return v4;
	} else if(!strcmp(n->name, "ADOPERATOR")) {
	    // 0: -, 1: +
	    int *v1 = (int*)malloc(1 * sizeof(int));
	    char **v2 = NULL;
	    Data *v3 = (Data*)malloc(1 * sizeof(Data));
	    Eval v4;
	    v3->data = v1;
	    v3->type = -1;
	    v4.environment = env;
	    v4.result = v3;
	
	    if(!strcmp(n->tokens[0], "+")) {
	        *v1 = 1;
	    } else {
	        *v1 = 0;
	    }
	
	    return v4;
	} else if(!strcmp(n->name, "MULOPERATOR")) {
	    // 0: /, 1: *
	    int *v1 = (int*)malloc(1 * sizeof(int));
	    char **v2 = NULL;
	    Data *v3 = (Data*)malloc(1 * sizeof(Data));
	    Eval v4;
	    v3->data = v1;
	    v3->type = -1;
	    v4.environment = env;
	    v4.result = v3;
	
	    if(!strcmp(n->tokens[0], "*")) {
	        *v1 = 1;
	    } else {
	        *v1 = 0;
	    }
	
	    return v4;
	} else if(!strcmp(n->name, "UNOPERATOR")) {
	    // 1: & 2: !
	    int *v1 = (int*)malloc(1 * sizeof(int));
	    char **v2 = NULL;
	    Data *v3 = (Data*)malloc(1 * sizeof(Data));
	    Eval v4;
	    v3->data = v1;
	    v3->type = -1;
	    v4.environment = env;
	    v4.result = v3;
	
	    if(!strcmp(n->tokens[0], "&")) {
	        *v1 = 1;
	    } else if(!strcmp(n->tokens[0], "!")) {
	        *v1 = 2;
	    }
	
	    return v4;
	} else if(!strcmp(n->name, "Expr")) {
	    return evaluate_help(n->next[0], env);
	} else if(!strcmp(n->name, "OrExpr")) {
	    if(n->n_next == 2) {
	        Data *d = (Data*)malloc(1 * sizeof(Data));
	        Data *r1 = evaluate_help(n->next[0], env).result;
	        Data *r2 = evaluate_help(n->next[1], env).result;
	
	        if(r1->type == 1 && r2->type == 1) {
	            int *a = r1->data;
	            int *b = r2->data;
	            int *v = (int*)malloc(1 * sizeof(int));
	            *v = (*a) || (*b);
	            d->data = v;
	            d->type = 1;
	        } else {
	            printf("Execute Error: OrExpr only takes booleans.\n");
	            exit(0);
	        }
	
	        Eval e;
	        e.environment = env;
	        e.result = d;
	        return e;
	    } else {
	        return evaluate_help(n->next[0], env);
	    }
	} else if(!strcmp(n->name, "AndExpr")) {
	    if(n->n_next == 2) {
	        Data *d = (Data*)malloc(1 * sizeof(Data));
	        Data *r1 = evaluate_help(n->next[0], env).result;
	        Data *r2 = evaluate_help(n->next[1], env).result;
	
	        if(r1->type == 1 && r2->type == 1) {
	            int *a = r1->data;
	            int *b = r2->data;
	            int *v = (int*)malloc(1 * sizeof(int));
	            *v = (*a) && (*b);
	            d->data = v;
	            d->type = 1;
	        } else {
	            printf("Execute Error: AndExpr only takes booleans.\n");
	            exit(0);
	        }
	
	        Eval e;
	        e.environment = env;
	        e.result = d;
	        return e;
	    } else {
	        return evaluate_help(n->next[0], env);
	    }
	} else if(!strcmp(n->name, "EqualityExpr")) {
	    if(n->n_next == 3) {
	        Data *d = (Data*)malloc(1 * sizeof(Data));
	        Data *r1 = evaluate_help(n->next[0], env).result;
	        Data *r2 = evaluate_help(n->next[2], env).result;
	        int *op = evaluate_help(n->next[1], env).result->data;
	
	        if(r1->type == 0 && r2->type == 0) {
	            int *a = r1->data;
	            int *b = r2->data;
	            int *v = (int*)malloc(1 * sizeof(int));
	            if(*op == 1) {
	                *v = (*a) == (*b);
	            } else {
	                *v = (*a) != (*b);
	            }
	            d->data = v;
	            d->type = 1;
	        } else if(r1->type == 2 && r2->type == 2) {
	            float *a = r1->data;
	            float *b = r2->data;
	            int *v = (int*)malloc(1 * sizeof(int));
	            if(*op == 1) {
	                *v = (*a) == (*b);
	            } else {
	                *v = (*a) != (*b);
	            }
	            d->data = v;
	            d->type = 1;
	        } else if(r1->type == 3 && r2->type == 3) {
	            char *a = r1->data;
	            char *b = r2->data;
	            int *v = (int*)malloc(1 * sizeof(int));
	            if(*op == 1) {
	                *v = (*a) == (*b);
	            } else {
	                *v = (*a) != (*b);
	            }
	            d->data = v;
	            d->type = 1;
	        } else if(r1->type == 1 && r2->type == 1) {
	            int *a = r1->data;
	            int *b = r2->data;
	            int *v = (int*)malloc(1 * sizeof(int));
	            if(*op == 1) {
	                *v = (*a) == (*b);
	            } else {
	                *v = (*a) != (*b);
	            }
	            d->data = v;
	            d->type = 1;
	        } else {
	            printf("Execute Error: Equality Expr only takes integer, float, bool, and char.\n");
	            exit(0);
	        }
	
	        Eval e;
	        e.environment = env;
	        e.result = d;
	        return e;
	    } else {
	        return evaluate_help(n->next[0], env);
	    }
	} else if(!strcmp(n->name, "RelationalExpr")) {
	    if(n->n_next == 3) {
	        Data *d = (Data*)malloc(1 * sizeof(Data));
	        Data *r1 = evaluate_help(n->next[0], env).result;
	        Data *r2 = evaluate_help(n->next[2], env).result;
	        int *op = evaluate_help(n->next[1], env).result->data;
	
	        if(r1->type == 0 && r2->type == 0) {
	            int *a = r1->data;
	            int *b = r2->data;
	            int *v = (int*)malloc(1 * sizeof(int));
	            if(*op == 0) {
	                *v = (*a) < (*b);
	            } else if(*op == 1) {
	                *v = (*a) > (*b);
	            } else if(*op == 2) {
	                *v = (*a) <= (*b);
	            } else {
	                *v = (*a) >= (*b);
	            }
	            d->data = v;
	            d->type = 1;
	        } else if(r1->type == 2 && r2->type == 2) {
	            float *a = r1->data;
	            float *b = r2->data;
	            int *v = (int*)malloc(1 * sizeof(int));
	            
	            if(*op == 0) {
	                *v = (*a) < (*b);
	            } else if(*op == 1) {
	                *v = (*a) > (*b);
	            } else if(*op == 2) {
	                *v = (*a) <= (*b);
	            } else {
	                *v = (*a) >= (*b);
	            }
	            d->data = v;
	            d->type = 1;
	        } else if(r1->type == 3 && r2->type == 3) {
	            char *a = r1->data;
	            char *b = r2->data;
	            int *v = (int*)malloc(1 * sizeof(int));
	            
	            if(*op == 0) {
	                *v = (*a) < (*b);
	            } else if(*op == 1) {
	                *v = (*a) > (*b);
	            } else if(*op == 2) {
	                *v = (*a) <= (*b);
	            } else {
	                *v = (*a) >= (*b);
	            }
	            d->data = v;
	            d->type = 1;
	        } else {
	            printf("Execute Error: Relational expression only takes integers, floats, and characters.\n");
	            exit(0);
	        }
	
	        Eval e;
	        e.environment = env;
	        e.result = d;
	        return e;
	    } else {
	        return evaluate_help(n->next[0], env);
	    }
	} else if(!strcmp(n->name, "AdditiveExpr")) {
	    if(n->n_next == 3) {
	        Data *d = (Data*)malloc(1 * sizeof(Data));
	        Data *r1 = evaluate_help(n->next[0], env).result;
	        Data *r2 = evaluate_help(n->next[2], env).result;
	        int *op = evaluate_help(n->next[1], env).result->data;
	
	        if(r1->type == 0 && r2->type == 0) {
	            int *a = r1->data;
	            int *b = r2->data;
	            int *v = (int*)malloc(1 * sizeof(int));
	            if(*op) {
	                *v = (*a) + (*b);
	            } else {
	                *v = (*a) - (*b);
	            }
	            d->data = v;
	            d->type = 0;
	        } else if(r1->type == 2 && r2->type == 2) {
	            float *a = r1->data;
	            float *b = r2->data;
	            float *v = (float*)malloc(1 * sizeof(float));
	            if(*op) {
	                *v = (*a) + (*b);
	            } else {
	                *v = (*a) - (*b);
	            }
	            d->data = v;
	            d->type = 2;
	        } else {
	            printf("Execute Error: Additive expression only takes integers and floats.\n");
	            exit(0);
	        }
	
	        Eval e;
	        e.environment = env;
	        e.result = d;
	        return e;
	    } else {
	        return evaluate_help(n->next[0], env);
	    }
	} else if(!strcmp(n->name, "MultiplicativeExpr")) {
	    if(n->n_next == 3) {
	        Data *d = (Data*)malloc(1 * sizeof(Data));
	        Data *r1 = evaluate_help(n->next[0], env).result;
	        Data *r2 = evaluate_help(n->next[2], env).result;
	        int *op = evaluate_help(n->next[1], env).result->data;
	
	        if(r1->type == 0 && r2->type == 0) {
	            int *a = r1->data;
	            int *b = r2->data;
	            int *v = (int*)malloc(1 * sizeof(int));
	            if(*op) {
	                *v = (*a) * (*b);
	            } else {
	                *v = (*a) / (*b);
	            }
	            d->data = v;
	            d->type = 0;
	        } else if(r1->type == 2 && r2->type == 2) {
	            float *a = r1->data;
	            float *b = r2->data;
	            float *v = (float*)malloc(1 * sizeof(float));
	            if(*op) {
	                *v = (*a) * (*b);
	            } else {
	                *v = (*a) / (*b);
	            }
	            d->data = v;
	            d->type = 2;
	        } else {
	            printf("Execute Error: Multiplicative expression only takes integers and floats.\n");
	            exit(0);
	        }
	
	        Eval e;
	        e.environment = env;
	        e.result = d;
	        return e;
	    } else {
	        return evaluate_help(n->next[0], env);
	    }
	} else if(!strcmp(n->name, "PowerExpr")) {
	    if(n->n_next == 2) {
	        Data *d = (Data*)malloc(1 * sizeof(Data));
	        Data *r1 = evaluate_help(n->next[0], env).result;
	        Data *r2 = evaluate_help(n->next[1], env).result;
	
	        if(r1->type == 0 && r2->type == 0) {
	            int *a = r1->data;
	            int *b = r2->data;
	            int i = 0;
	            int *v = (int*)malloc(1 * sizeof(int));
	            *v = 1;
	            for(i = 0; i < *b; i++) {
	                *v *= *a;
	            }
	            d->data = v;
	            d->type = 0;
	        } else {
	            printf("Execute Error: Power expression only takes integers.\n");
	            exit(0);
	        }
	
	        Eval e;
	        e.environment = env;
	        e.result = d;
	        return e;
	    } else {
	        return evaluate_help(n->next[0], env);
	    }
	} else if(!strcmp(n->name, "UnaryExpr")) {
	    if(n->n_next == 2) {
	        Data *d = (Data*)malloc(1 * sizeof(Data));
	        int *op = evaluate_help(n->next[0], env).result->data;
	        int *r = evaluate_help(n->next[1], env).result->data;
	        int *v = (int*)malloc(1 * sizeof(int));
	        if(*op == 1) {
	            *v = &r;
	            d->data = v;
	            d->type = 4;
	        } else {
	            if(*r) {
	                *v = 0;
	            } else {
	                *v = 1;
	            }
	            d->data = v;
	            d->type = 1;
	        }
	
	        Eval e;
	        e.environment = env;
	        e.result = d;
	        return e;
	    } else {
	        return evaluate_help(n->next[0], env);
	    }
	} else if(!strcmp(n->name, "PrimaryExpr")) {
	    if(n->n_next == 1) {
	        if(!strcmp(n->tokens[0], "(")) {
	            return evaluate_help(n->next[0], env);
	        } else {
	            HashMap *h;
	            h = init(h);
	            Data *function_casing = get_hashmap(n->tokens[1], env);
	            Data *args = evaluate_help(n->next[0], env).result;
	            if(args->n_args != function_casing->n_args) {
	                printf("Function arguments are invalid.\n");
	                exit(0);
	            }
	            int i;
	            Data **a_input = (Data**)args->data;
	            for(i = 0; i < function_casing->n_args; i++) {
	                set_hashmap(function_casing->arg_names[i], a_input[i], h);
	            }
	
	            Data *l = evaluate_help(function_casing->data, h).result;
	            if(l->type != function_casing->type) {
	                printf("Return type invalid.\n");
	                exit(0);
	            }
	
	            Eval e;
	            e.result = l;
	            e.environment = env;
	            return e;
	        }
	    } else {
	        char *v = n->tokens[0];
	        Data *d = (Data*)malloc(1 * sizeof(Data));
	        if(match(v, "^[0-9]+$")) {
	            int *r = (int*)malloc(1 * sizeof(int));
	            *r = atoi(v);
	            d->data = r;
	            d->type = 0;
	        } else if(match(v, "^true|false$")) {
	            int *r = (int*)malloc(1 * sizeof(int));
	            if(!strcmp(v, "true")) {
	                *r = 1;
	            } else {
	                *r = 0;
	            }
	            d->data = r;
	            d->type = 1;
	        } else if(match(v, "^[0-9]+\\.[0-9]*$")) {
	            float *r = (float*)malloc(1 * sizeof(float));
	            *r = atof(v);
	            d->data = r;
	            d->type = 2;
	        } else if(match(v, "^'.'$")) {
	            char *r = (char*)malloc(1 * sizeof(char));
	            *r = v[1];
	            d->data = r;
	            d->type = 3;
	        } else {
	            d = get_hashmap(v, env);
	        }
	
	        Eval e;
	        e.environment = env;
	        e.result = d;
	        return e;
	    }
	} else if(!strcmp(n->name, "ArgsCall")) {
	    if(n->n_next == 1) {
	        Data *r = (Data*)malloc(1 * sizeof(Data));
	        Data **sr = (Data**)malloc(1 * sizeof(Data*));
	        sr[0] = evaluate_help(n->next[0], env).result;
	        r->data = sr;
	        r->n_args = 1;
	
	        Eval e;
	        e.environment = env;
	        e.result = r;
	        return e;
	    } else {
	        Data *d = (Data*)malloc(1 * sizeof(Data));
	        Data *r1 = evaluate_help(n->next[0], env).result;
	        Data *r2 = evaluate_help(n->next[1], env).result;
	        Data **sr = (Data**)malloc((r2->n_args + 1) * sizeof(Data*));
	        int i;
	        sr[0] = r1;
	        Data **a = r2->data;
	        for(i = 0; i < r2->n_args; i++) {
	            sr[i + 1] = a[i];
	        }
	        d->data = sr;
	        d->n_args = r2->n_args + 1;
	
	        Eval e;
	        e.environment = env;
	        e.result = d;
	        return e;
	    }
	} else if(!strcmp(n->name, "Type")) {
	    Data *d = (Data*)malloc(1 * sizeof(Data));
	    d->data = NULL;
	    if(!strcmp(n->tokens[0], "int")) {
	        d->type = 0;
	    } else if(!strcmp(n->tokens[0], "bool")) {
	        d->type = 1;
	    } else if(!strcmp(n->tokens[0], "float")) {
	        d->type = 2;
	    } else {
	        d->type = 3;
	    }
	
	    Eval e;
	    e.environment = env;
	    e.result = d;
	    return e;
	} else if(!strcmp(n->name, "Stmt")) {
	    Eval r = evaluate_help(n->next[0], env);
	    if(n->n_next == 2) {
	        return evaluate_help(n->next[1], r.environment);
	    }
	
	    return r;
	} else if(!strcmp(n->name, "StmtOptions")) {
	    return evaluate_help(n->next[0], env);
	} else if(!strcmp(n->name, "DeclareStmt")) {
	    Eval r = evaluate_help(n->next[0], env);
	    Data *d = (Data*)malloc(1 * sizeof(Data));
	    d->type = r.result->type;
	    d->data = NULL;
	
	    set_hashmap(n->tokens[0], d, env);
	
	    Eval e;
	    e.environment = env;
	    e.result = d;
	    return e;
	} else if(!strcmp(n->name, "AssignStmt")) {
	    Eval r = evaluate_help(n->next[0], env);
	    set_hashmap(n->tokens[0], r.result, env);
	    Eval e;
	    e.result = NULL;
	    e.environment = env;
	    return e;
	} else if(!strcmp(n->name, "PrintStmt")) {
	    Eval r = evaluate_help(n->next[0], env);
	    if(r.result->type == 0) {
	        int *p = r.result->data;
	        printf("%d\n", *p);
	    } else if(r.result->type == 1) {
	        int *p = r.result->data;
	        printf("%d\n", *p);
	    } else if(r.result->type == 2) {
	        float *p = r.result->data;
	        printf("%f\n", *p);
	    } else {
	        char *p = r.result->data;
	        printf("%c\n", *p);
	    }
	
	    Eval e;
	    e.result = NULL;
	    e.environment = env;
	    return e;
	} else if(!strcmp(n->name, "IfStmt")) {
	    Eval r = evaluate_help(n->next[0], env);
	    int *d = r.result->data;
	    if(*d) {
	        return evaluate_help(n->next[1], env);
	    } else {
	        return evaluate_help(n->next[2], env);
	    }
	} else if(!strcmp(n->name, "ElseBranch")) {
	    if(n->n_next == 0) {
	        Eval e;
	        e.result = NULL;
	        e.environment = env;
	        return e;
	    } else {
	        return evaluate_help(n->next[0], env);
	    }
	} else if(!strcmp(n->name, "WhileStmt")) {
	    Eval r = evaluate_help(n->next[0], env);
	    int *d = r.result->data;
	    while(*d) {
	        Eval e = evaluate_help(n->next[1], env);
	        env = e.environment;
	        r = evaluate_help(n->next[0], env);
	        d = r.result->data;
	    }
	
	    Eval e;
	    e.result = NULL;
	    e.environment = env;
	    return e;
	} else if(!strcmp(n->name, "ReturnStmt")) {
	    return evaluate_help(n->next[0], env);
	} else if(!strcmp(n->name, "Super")) {
	    Eval r = evaluate_help(n->next[0], env);
	    if(n->n_next == 2) {
	        return evaluate_help(n->next[1], r.environment);
	    }
	
	    return r;
	} else if(!strcmp(n->name, "SuperOptions")) {
	    return evaluate_help(n->next[0], env);
	} else if(!strcmp(n->name, "Function")) {
	    // We have 2 important trees
	    Data *d = (Data*)malloc(1 * sizeof(Data));
	    HashMap  *h;
	    h = init(h);
	    // get the args
	    evaluate_help(n->next[1], h);
	    // h has args
	    int len;
	    char **names;
	    Data **lst = get_all_hashmap(h, &len, &names);
	    d->arg_names = names;
	    d->n_args = len;
	    d->args = lst;
	    d->data = n->next[2];
	    d->type = evaluate_help(n->next[0], env).result->type;
	    set_hashmap(n->tokens[1], d, env);
	    Eval e;
	    e.environment = env;
	    e.result = NULL;
	    return e;
	} else if(!strcmp(n->name, "Args")) {
	    Eval r = evaluate_help(n->next[0], env);
	    if(n->n_next == 2) {
	        return evaluate_help(n->next[1], r.environment);
	    }
	
	    return r;
	} else if(!strcmp(n->name, "Arg")) {
	    Eval r = evaluate_help(n->next[0], env);
	    Data *d = (Data*)malloc(1 * sizeof(Data));
	    d->type = r.result->type;
	    d->data = NULL;
	
	    set_hashmap(n->tokens[0], d, env);
	
	    Eval e;
	    e.environment = env;
	    e.result = d;
	    return e;
	}
}