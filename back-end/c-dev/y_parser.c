#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "y_parser.h"

node_t* parse_clean(node_t *n) {
    if(n->n_next == 1 && n->n_tokens == 0) {
        return parse_clean(n->next[0]);
    } else {
        int i;
        for(i = 0; i < n->n_next; i++) {
            n->next[i] = parse_clean(n->next[i]);
        }

        return n;
    }
}

node_t* parse(token_t *h) {
	return parse_stmt(h).node;
}

void s_move(char *dest, char *src) {
    int i = 0;
    while(src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = src[i];
}

int lookahead(token_t *h) {
    return (h != NULL? h->index : -1);
}

token_t* match_token(token_t *h, int v) {
    if(lookahead(h) == v) {
        return h->next;
    } else {
        printf("Parse Error: Unexpected token -> %s\n", h->value);
        exit(0);
    }

    return NULL;
}

tuple_t parse_stmtop(token_t *h) {
	node_t *r = (node_t*)malloc(1 * sizeof(node_t));
	r->tokens = (char**)malloc(1 * sizeof(char*));
	r->n_tokens = 0;
	r->next = (node_t**)malloc(1 * sizeof(node_t*));
	r->n_next = 0;
	r->name = (char*)malloc(6 * sizeof(char));
	s_move(r->name, "stmtop");

	if(lookahead(h) == 3) {
		tuple_t t = parse_if(h);
		h = t.token;
		r->next = realloc(r->next, (r->n_next + 1) * sizeof(node_t*));
		r->n_next++;
		r->next[r->n_next - 1] = t.node;

		tuple_t rt;
		rt.token = h;
		rt.node = r;
		return rt;
	} else if(lookahead(h) == 0) {
		tuple_t t = parse_while(h);
		h = t.token;
		r->next = realloc(r->next, (r->n_next + 1) * sizeof(node_t*));
		r->n_next++;
		r->next[r->n_next - 1] = t.node;

		tuple_t rt;
		rt.token = h;
		rt.node = r;
		return rt;
	} else if(lookahead(h) == 1) {
		tuple_t t = parse_print(h);
		h = t.token;
		r->next = realloc(r->next, (r->n_next + 1) * sizeof(node_t*));
		r->n_next++;
		r->next[r->n_next - 1] = t.node;

		tuple_t rt;
		rt.token = h;
		rt.node = r;
		return rt;
	} else {
		printf("Parse Error: Token -> %s\n", h->value);
		exit(0);
	}

	printf("Parse Error: Token -> %s\n", h->value);
	exit(0);
}

tuple_t parse_if(token_t *h) {
	node_t *r = (node_t*)malloc(1 * sizeof(node_t));
	r->tokens = (char**)malloc(1 * sizeof(char*));
	r->n_tokens = 0;
	r->next = (node_t**)malloc(1 * sizeof(node_t*));
	r->n_next = 0;
	r->name = (char*)malloc(2 * sizeof(char));
	s_move(r->name, "if");

	if(lookahead(h) == 3) {
		r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
		r->n_tokens++;
		r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
		s_move(r->tokens[r->n_tokens - 1], h->value);
		h = match_token(h, 3);

		if(lookahead(h) == 5) {
			r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
			r->n_tokens++;
			r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
			s_move(r->tokens[r->n_tokens - 1], h->value);
			h = match_token(h, 5);

			if(lookahead(h) == 8 || lookahead(h) == 9) {
				tuple_t t = parse_expr(h);
				h = t.token;
				r->next = realloc(r->next, (r->n_next + 1) * sizeof(node_t*));
				r->n_next++;
				r->next[r->n_next - 1] = t.node;

				if(lookahead(h) == 4) {
					r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
					r->n_tokens++;
					r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
					s_move(r->tokens[r->n_tokens - 1], h->value);
					h = match_token(h, 4);

					if(lookahead(h) == 6) {
						r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
						r->n_tokens++;
						r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
						s_move(r->tokens[r->n_tokens - 1], h->value);
						h = match_token(h, 6);

						if(lookahead(h) == 3 || lookahead(h) == 0 || lookahead(h) == 1) {
							tuple_t t = parse_stmt(h);
							h = t.token;
							r->next = realloc(r->next, (r->n_next + 1) * sizeof(node_t*));
							r->n_next++;
							r->next[r->n_next - 1] = t.node;

							if(lookahead(h) == 7) {
								r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
								r->n_tokens++;
								r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
								s_move(r->tokens[r->n_tokens - 1], h->value);
								h = match_token(h, 7);

								tuple_t rt;
								rt.token = h;
								rt.node = r;
								return rt;
							}
						}
					}
				}
			}
		}
	} else {
		printf("Parse Error: Token -> %s\n", h->value);
		exit(0);
	}

	printf("Parse Error: Token -> %s\n", h->value);
	exit(0);
}

tuple_t parse_while(token_t *h) {
	node_t *r = (node_t*)malloc(1 * sizeof(node_t));
	r->tokens = (char**)malloc(1 * sizeof(char*));
	r->n_tokens = 0;
	r->next = (node_t**)malloc(1 * sizeof(node_t*));
	r->n_next = 0;
	r->name = (char*)malloc(5 * sizeof(char));
	s_move(r->name, "while");

	if(lookahead(h) == 0) {
		r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
		r->n_tokens++;
		r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
		s_move(r->tokens[r->n_tokens - 1], h->value);
		h = match_token(h, 0);

		if(lookahead(h) == 5) {
			r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
			r->n_tokens++;
			r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
			s_move(r->tokens[r->n_tokens - 1], h->value);
			h = match_token(h, 5);

			if(lookahead(h) == 8 || lookahead(h) == 9) {
				tuple_t t = parse_expr(h);
				h = t.token;
				r->next = realloc(r->next, (r->n_next + 1) * sizeof(node_t*));
				r->n_next++;
				r->next[r->n_next - 1] = t.node;

				if(lookahead(h) == 4) {
					r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
					r->n_tokens++;
					r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
					s_move(r->tokens[r->n_tokens - 1], h->value);
					h = match_token(h, 4);

					if(lookahead(h) == 6) {
						r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
						r->n_tokens++;
						r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
						s_move(r->tokens[r->n_tokens - 1], h->value);
						h = match_token(h, 6);

						if(lookahead(h) == 3 || lookahead(h) == 0 || lookahead(h) == 1) {
							tuple_t t = parse_stmt(h);
							h = t.token;
							r->next = realloc(r->next, (r->n_next + 1) * sizeof(node_t*));
							r->n_next++;
							r->next[r->n_next - 1] = t.node;

							if(lookahead(h) == 7) {
								r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
								r->n_tokens++;
								r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
								s_move(r->tokens[r->n_tokens - 1], h->value);
								h = match_token(h, 7);

								tuple_t rt;
								rt.token = h;
								rt.node = r;
								return rt;
							}
						}
					}
				}
			}
		}
	} else {
		printf("Parse Error: Token -> %s\n", h->value);
		exit(0);
	}

	printf("Parse Error: Token -> %s\n", h->value);
	exit(0);
}

tuple_t parse_stmt(token_t *h) {
	node_t *r = (node_t*)malloc(1 * sizeof(node_t));
	r->tokens = (char**)malloc(1 * sizeof(char*));
	r->n_tokens = 0;
	r->next = (node_t**)malloc(1 * sizeof(node_t*));
	r->n_next = 0;
	r->name = (char*)malloc(4 * sizeof(char));
	s_move(r->name, "stmt");

	tuple_t t = parse_stmtop(h);
	h = t.token;
	r->next = realloc(r->next, (r->n_next + 1) * sizeof(node_t*));
	r->n_next++;
	r->next[r->n_next - 1] = t.node;

	if(lookahead(h) == 3 || lookahead(h) == 0 || lookahead(h) == 1) {
		tuple_t t = parse_stmt(h);
		h = t.token;
		r->next = realloc(r->next, (r->n_next + 1) * sizeof(node_t*));
		r->n_next++;
		r->next[r->n_next - 1] = t.node;

		tuple_t rt;
		rt.token = h;
		rt.node = r;
		return rt;
	} else if(lookahead(h) == 2) {
		r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
		r->n_tokens++;
		r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
		s_move(r->tokens[r->n_tokens - 1], h->value);
		h = match_token(h, 2);

		tuple_t rt;
		rt.token = h;
		rt.node = r;
		return rt;
	} else {
		printf("Parse Error: Token -> %s\n", h->value);
		exit(0);
	}

	printf("Parse Error: Token -> %s\n", h->value);
	exit(0);
}

tuple_t parse_expr(token_t *h) {
	node_t *r = (node_t*)malloc(1 * sizeof(node_t));
	r->tokens = (char**)malloc(1 * sizeof(char*));
	r->n_tokens = 0;
	r->next = (node_t**)malloc(1 * sizeof(node_t*));
	r->n_next = 0;
	r->name = (char*)malloc(4 * sizeof(char));
	s_move(r->name, "expr");

	if(lookahead(h) == 8) {
		r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
		r->n_tokens++;
		r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
		s_move(r->tokens[r->n_tokens - 1], h->value);
		h = match_token(h, 8);

		tuple_t rt;
		rt.token = h;
		rt.node = r;
		return rt;
	} else if(lookahead(h) == 9) {
		r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
		r->n_tokens++;
		r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
		s_move(r->tokens[r->n_tokens - 1], h->value);
		h = match_token(h, 9);

		tuple_t rt;
		rt.token = h;
		rt.node = r;
		return rt;
	} else {
		printf("Parse Error: Token -> %s\n", h->value);
		exit(0);
	}

	printf("Parse Error: Token -> %s\n", h->value);
	exit(0);
}

tuple_t parse_print(token_t *h) {
	node_t *r = (node_t*)malloc(1 * sizeof(node_t));
	r->tokens = (char**)malloc(1 * sizeof(char*));
	r->n_tokens = 0;
	r->next = (node_t**)malloc(1 * sizeof(node_t*));
	r->n_next = 0;
	r->name = (char*)malloc(5 * sizeof(char));
	s_move(r->name, "print");

	if(lookahead(h) == 1) {
		r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
		r->n_tokens++;
		r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
		s_move(r->tokens[r->n_tokens - 1], h->value);
		h = match_token(h, 1);

		if(lookahead(h) == 5) {
			r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
			r->n_tokens++;
			r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
			s_move(r->tokens[r->n_tokens - 1], h->value);
			h = match_token(h, 5);

			if(lookahead(h) == 8 || lookahead(h) == 9) {
				tuple_t t = parse_expr(h);
				h = t.token;
				r->next = realloc(r->next, (r->n_next + 1) * sizeof(node_t*));
				r->n_next++;
				r->next[r->n_next - 1] = t.node;

				if(lookahead(h) == 4) {
					r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
					r->n_tokens++;
					r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
					s_move(r->tokens[r->n_tokens - 1], h->value);
					h = match_token(h, 4);

					tuple_t rt;
					rt.token = h;
					rt.node = r;
					return rt;
				}
			}
		}
	} else {
		printf("Parse Error: Token -> %s\n", h->value);
		exit(0);
	}

	printf("Parse Error: Token -> %s\n", h->value);
	exit(0);
}

