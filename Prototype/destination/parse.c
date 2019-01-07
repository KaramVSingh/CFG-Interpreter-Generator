#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse.h"

Node* parse_clean(Node *n) {
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

Node* parse(Token *h) {
	return parse_clean(parse_Super(h).node);
}

void s_move(char *dest, char *src) {
    int i = 0;
    while(src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = src[i];
}

int lookahead(Token *h) {
    return (h != NULL? h->type : -1);
}

Token* match_token(Token *h, int v) {
    if(lookahead(h) == v) {
        return h->next;
    } else {
        printf("Parse Error: Unexpected token -> %s\n", h->value);
        exit(0);
    }

    return NULL;
}

Tuple parse_EQOPERATOR(Token *h) {
	Node *r = (Node*)malloc(1 * sizeof(Node));
	r->tokens = (char**)malloc(1 * sizeof(char*));
	r->n_tokens = 0;
	r->next = (Node**)malloc(1 * sizeof(Node*));
	r->n_next = 0;
	r->name = (char*)malloc(10 * sizeof(char));
	s_move(r->name, "EQOPERATOR");


	if(lookahead(h) == 11) {
		r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
		r->n_tokens++;
		r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
		s_move(r->tokens[r->n_tokens - 1], h->value);
		h = match_token(h, 11);

		Tuple rt;
		rt.token = h;
		rt.node = r;
		return rt;
	} else 	if(lookahead(h) == 12) {
		r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
		r->n_tokens++;
		r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
		s_move(r->tokens[r->n_tokens - 1], h->value);
		h = match_token(h, 12);

		Tuple rt;
		rt.token = h;
		rt.node = r;
		return rt;
	}
	printf("Parse Error: Token -> %s\n", h->value);
	exit(0);
}

Tuple parse_REOPERATOR(Token *h) {
	Node *r = (Node*)malloc(1 * sizeof(Node));
	r->tokens = (char**)malloc(1 * sizeof(char*));
	r->n_tokens = 0;
	r->next = (Node**)malloc(1 * sizeof(Node*));
	r->n_next = 0;
	r->name = (char*)malloc(10 * sizeof(char));
	s_move(r->name, "REOPERATOR");


	if(lookahead(h) == 18) {
		r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
		r->n_tokens++;
		r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
		s_move(r->tokens[r->n_tokens - 1], h->value);
		h = match_token(h, 18);

		Tuple rt;
		rt.token = h;
		rt.node = r;
		return rt;
	} else 	if(lookahead(h) == 19) {
		r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
		r->n_tokens++;
		r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
		s_move(r->tokens[r->n_tokens - 1], h->value);
		h = match_token(h, 19);

		Tuple rt;
		rt.token = h;
		rt.node = r;
		return rt;
	} else 	if(lookahead(h) == 13) {
		r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
		r->n_tokens++;
		r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
		s_move(r->tokens[r->n_tokens - 1], h->value);
		h = match_token(h, 13);

		Tuple rt;
		rt.token = h;
		rt.node = r;
		return rt;
	} else 	if(lookahead(h) == 14) {
		r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
		r->n_tokens++;
		r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
		s_move(r->tokens[r->n_tokens - 1], h->value);
		h = match_token(h, 14);

		Tuple rt;
		rt.token = h;
		rt.node = r;
		return rt;
	}
	printf("Parse Error: Token -> %s\n", h->value);
	exit(0);
}

Tuple parse_ADOPERATOR(Token *h) {
	Node *r = (Node*)malloc(1 * sizeof(Node));
	r->tokens = (char**)malloc(1 * sizeof(char*));
	r->n_tokens = 0;
	r->next = (Node**)malloc(1 * sizeof(Node*));
	r->n_next = 0;
	r->name = (char*)malloc(10 * sizeof(char));
	s_move(r->name, "ADOPERATOR");


	if(lookahead(h) == 20) {
		r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
		r->n_tokens++;
		r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
		s_move(r->tokens[r->n_tokens - 1], h->value);
		h = match_token(h, 20);

		Tuple rt;
		rt.token = h;
		rt.node = r;
		return rt;
	} else 	if(lookahead(h) == 21) {
		r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
		r->n_tokens++;
		r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
		s_move(r->tokens[r->n_tokens - 1], h->value);
		h = match_token(h, 21);

		Tuple rt;
		rt.token = h;
		rt.node = r;
		return rt;
	}
	printf("Parse Error: Token -> %s\n", h->value);
	exit(0);
}

Tuple parse_MULOPERATOR(Token *h) {
	Node *r = (Node*)malloc(1 * sizeof(Node));
	r->tokens = (char**)malloc(1 * sizeof(char*));
	r->n_tokens = 0;
	r->next = (Node**)malloc(1 * sizeof(Node*));
	r->n_next = 0;
	r->name = (char*)malloc(11 * sizeof(char));
	s_move(r->name, "MULOPERATOR");


	if(lookahead(h) == 22) {
		r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
		r->n_tokens++;
		r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
		s_move(r->tokens[r->n_tokens - 1], h->value);
		h = match_token(h, 22);

		Tuple rt;
		rt.token = h;
		rt.node = r;
		return rt;
	} else 	if(lookahead(h) == 23) {
		r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
		r->n_tokens++;
		r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
		s_move(r->tokens[r->n_tokens - 1], h->value);
		h = match_token(h, 23);

		Tuple rt;
		rt.token = h;
		rt.node = r;
		return rt;
	}
	printf("Parse Error: Token -> %s\n", h->value);
	exit(0);
}

Tuple parse_UNOPERATOR(Token *h) {
	Node *r = (Node*)malloc(1 * sizeof(Node));
	r->tokens = (char**)malloc(1 * sizeof(char*));
	r->n_tokens = 0;
	r->next = (Node**)malloc(1 * sizeof(Node*));
	r->n_next = 0;
	r->name = (char*)malloc(10 * sizeof(char));
	s_move(r->name, "UNOPERATOR");


	if(lookahead(h) == 24) {
		r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
		r->n_tokens++;
		r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
		s_move(r->tokens[r->n_tokens - 1], h->value);
		h = match_token(h, 24);

		Tuple rt;
		rt.token = h;
		rt.node = r;
		return rt;
	} else 	if(lookahead(h) == 25) {
		r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
		r->n_tokens++;
		r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
		s_move(r->tokens[r->n_tokens - 1], h->value);
		h = match_token(h, 25);

		Tuple rt;
		rt.token = h;
		rt.node = r;
		return rt;
	}
	printf("Parse Error: Token -> %s\n", h->value);
	exit(0);
}

Tuple parse_Expr(Token *h) {
	Node *r = (Node*)malloc(1 * sizeof(Node));
	r->tokens = (char**)malloc(1 * sizeof(char*));
	r->n_tokens = 0;
	r->next = (Node**)malloc(1 * sizeof(Node*));
	r->n_next = 0;
	r->name = (char*)malloc(4 * sizeof(char));
	s_move(r->name, "Expr");

	Tuple t = parse_OrExpr(h);
	h = t.token;
	r->next = realloc(r->next, (r->n_next + 1) * sizeof(Node*));
	r->n_next++;
	r->next[r->n_next - 1] = t.node;

	Tuple rt;
	rt.token = h;
	rt.node = r;
	return rt;

	printf("Parse Error: Token -> %s\n", h->value);
	exit(0);
}

Tuple parse_OrExpr(Token *h) {
	Node *r = (Node*)malloc(1 * sizeof(Node));
	r->tokens = (char**)malloc(1 * sizeof(char*));
	r->n_tokens = 0;
	r->next = (Node**)malloc(1 * sizeof(Node*));
	r->n_next = 0;
	r->name = (char*)malloc(6 * sizeof(char));
	s_move(r->name, "OrExpr");

	Tuple t = parse_AndExpr(h);
	h = t.token;
	r->next = realloc(r->next, (r->n_next + 1) * sizeof(Node*));
	r->n_next++;
	r->next[r->n_next - 1] = t.node;

	if(lookahead(h) == 15) {
		r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
		r->n_tokens++;
		r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
		s_move(r->tokens[r->n_tokens - 1], h->value);
		h = match_token(h, 15);

		if(lookahead(h) == 24 || lookahead(h) == 25 || lookahead(h) == 36 || lookahead(h) == 37 || lookahead(h) == 35 || lookahead(h) == 38 || lookahead(h) == 39 || lookahead(h) == 5 || lookahead(h) == 27) {
			Tuple t = parse_OrExpr(h);
			h = t.token;
			r->next = realloc(r->next, (r->n_next + 1) * sizeof(Node*));
			r->n_next++;
			r->next[r->n_next - 1] = t.node;
			Tuple rt;
			rt.token = h;
			rt.node = r;
			return rt;
		}
	} else {
		Tuple rt;
		rt.token = h;
		rt.node = r;
		return rt;
	}

	printf("Parse Error: Token -> %s\n", h->value);
	exit(0);
}

Tuple parse_AndExpr(Token *h) {
	Node *r = (Node*)malloc(1 * sizeof(Node));
	r->tokens = (char**)malloc(1 * sizeof(char*));
	r->n_tokens = 0;
	r->next = (Node**)malloc(1 * sizeof(Node*));
	r->n_next = 0;
	r->name = (char*)malloc(7 * sizeof(char));
	s_move(r->name, "AndExpr");

	Tuple t = parse_EqualityExpr(h);
	h = t.token;
	r->next = realloc(r->next, (r->n_next + 1) * sizeof(Node*));
	r->n_next++;
	r->next[r->n_next - 1] = t.node;

	if(lookahead(h) == 16) {
		r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
		r->n_tokens++;
		r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
		s_move(r->tokens[r->n_tokens - 1], h->value);
		h = match_token(h, 16);

		if(lookahead(h) == 24 || lookahead(h) == 25 || lookahead(h) == 36 || lookahead(h) == 37 || lookahead(h) == 35 || lookahead(h) == 38 || lookahead(h) == 39 || lookahead(h) == 5 || lookahead(h) == 27) {
			Tuple t = parse_AndExpr(h);
			h = t.token;
			r->next = realloc(r->next, (r->n_next + 1) * sizeof(Node*));
			r->n_next++;
			r->next[r->n_next - 1] = t.node;
			Tuple rt;
			rt.token = h;
			rt.node = r;
			return rt;
		}
	} else {
		Tuple rt;
		rt.token = h;
		rt.node = r;
		return rt;
	}

	printf("Parse Error: Token -> %s\n", h->value);
	exit(0);
}

Tuple parse_EqualityExpr(Token *h) {
	Node *r = (Node*)malloc(1 * sizeof(Node));
	r->tokens = (char**)malloc(1 * sizeof(char*));
	r->n_tokens = 0;
	r->next = (Node**)malloc(1 * sizeof(Node*));
	r->n_next = 0;
	r->name = (char*)malloc(12 * sizeof(char));
	s_move(r->name, "EqualityExpr");

	Tuple t = parse_RelationalExpr(h);
	h = t.token;
	r->next = realloc(r->next, (r->n_next + 1) * sizeof(Node*));
	r->n_next++;
	r->next[r->n_next - 1] = t.node;

	if(lookahead(h) == 11 || lookahead(h) == 12) {
		Tuple t = parse_EQOPERATOR(h);
		h = t.token;
		r->next = realloc(r->next, (r->n_next + 1) * sizeof(Node*));
		r->n_next++;
		r->next[r->n_next - 1] = t.node;
		if(lookahead(h) == 24 || lookahead(h) == 25 || lookahead(h) == 36 || lookahead(h) == 37 || lookahead(h) == 35 || lookahead(h) == 38 || lookahead(h) == 39 || lookahead(h) == 5 || lookahead(h) == 27) {
			Tuple t = parse_EqualityExpr(h);
			h = t.token;
			r->next = realloc(r->next, (r->n_next + 1) * sizeof(Node*));
			r->n_next++;
			r->next[r->n_next - 1] = t.node;
			Tuple rt;
			rt.token = h;
			rt.node = r;
			return rt;
		}
	} else {
		Tuple rt;
		rt.token = h;
		rt.node = r;
		return rt;
	}

	printf("Parse Error: Token -> %s\n", h->value);
	exit(0);
}

Tuple parse_RelationalExpr(Token *h) {
	Node *r = (Node*)malloc(1 * sizeof(Node));
	r->tokens = (char**)malloc(1 * sizeof(char*));
	r->n_tokens = 0;
	r->next = (Node**)malloc(1 * sizeof(Node*));
	r->n_next = 0;
	r->name = (char*)malloc(14 * sizeof(char));
	s_move(r->name, "RelationalExpr");

	Tuple t = parse_AdditiveExpr(h);
	h = t.token;
	r->next = realloc(r->next, (r->n_next + 1) * sizeof(Node*));
	r->n_next++;
	r->next[r->n_next - 1] = t.node;

	if(lookahead(h) == 18 || lookahead(h) == 19 || lookahead(h) == 13 || lookahead(h) == 14) {
		Tuple t = parse_REOPERATOR(h);
		h = t.token;
		r->next = realloc(r->next, (r->n_next + 1) * sizeof(Node*));
		r->n_next++;
		r->next[r->n_next - 1] = t.node;
		if(lookahead(h) == 24 || lookahead(h) == 25 || lookahead(h) == 36 || lookahead(h) == 37 || lookahead(h) == 35 || lookahead(h) == 38 || lookahead(h) == 39 || lookahead(h) == 5 || lookahead(h) == 27) {
			Tuple t = parse_RelationalExpr(h);
			h = t.token;
			r->next = realloc(r->next, (r->n_next + 1) * sizeof(Node*));
			r->n_next++;
			r->next[r->n_next - 1] = t.node;
			Tuple rt;
			rt.token = h;
			rt.node = r;
			return rt;
		}
	} else {
		Tuple rt;
		rt.token = h;
		rt.node = r;
		return rt;
	}

	printf("Parse Error: Token -> %s\n", h->value);
	exit(0);
}

Tuple parse_AdditiveExpr(Token *h) {
	Node *r = (Node*)malloc(1 * sizeof(Node));
	r->tokens = (char**)malloc(1 * sizeof(char*));
	r->n_tokens = 0;
	r->next = (Node**)malloc(1 * sizeof(Node*));
	r->n_next = 0;
	r->name = (char*)malloc(12 * sizeof(char));
	s_move(r->name, "AdditiveExpr");

	Tuple t = parse_MultiplicativeExpr(h);
	h = t.token;
	r->next = realloc(r->next, (r->n_next + 1) * sizeof(Node*));
	r->n_next++;
	r->next[r->n_next - 1] = t.node;

	if(lookahead(h) == 20 || lookahead(h) == 21) {
		Tuple t = parse_ADOPERATOR(h);
		h = t.token;
		r->next = realloc(r->next, (r->n_next + 1) * sizeof(Node*));
		r->n_next++;
		r->next[r->n_next - 1] = t.node;
		if(lookahead(h) == 24 || lookahead(h) == 25 || lookahead(h) == 36 || lookahead(h) == 37 || lookahead(h) == 35 || lookahead(h) == 38 || lookahead(h) == 39 || lookahead(h) == 5 || lookahead(h) == 27) {
			Tuple t = parse_AdditiveExpr(h);
			h = t.token;
			r->next = realloc(r->next, (r->n_next + 1) * sizeof(Node*));
			r->n_next++;
			r->next[r->n_next - 1] = t.node;
			Tuple rt;
			rt.token = h;
			rt.node = r;
			return rt;
		}
	} else {
		Tuple rt;
		rt.token = h;
		rt.node = r;
		return rt;
	}

	printf("Parse Error: Token -> %s\n", h->value);
	exit(0);
}

Tuple parse_MultiplicativeExpr(Token *h) {
	Node *r = (Node*)malloc(1 * sizeof(Node));
	r->tokens = (char**)malloc(1 * sizeof(char*));
	r->n_tokens = 0;
	r->next = (Node**)malloc(1 * sizeof(Node*));
	r->n_next = 0;
	r->name = (char*)malloc(18 * sizeof(char));
	s_move(r->name, "MultiplicativeExpr");

	Tuple t = parse_PowerExpr(h);
	h = t.token;
	r->next = realloc(r->next, (r->n_next + 1) * sizeof(Node*));
	r->n_next++;
	r->next[r->n_next - 1] = t.node;

	if(lookahead(h) == 22 || lookahead(h) == 23) {
		Tuple t = parse_MULOPERATOR(h);
		h = t.token;
		r->next = realloc(r->next, (r->n_next + 1) * sizeof(Node*));
		r->n_next++;
		r->next[r->n_next - 1] = t.node;
		if(lookahead(h) == 24 || lookahead(h) == 25 || lookahead(h) == 36 || lookahead(h) == 37 || lookahead(h) == 35 || lookahead(h) == 38 || lookahead(h) == 39 || lookahead(h) == 5 || lookahead(h) == 27) {
			Tuple t = parse_MultiplicativeExpr(h);
			h = t.token;
			r->next = realloc(r->next, (r->n_next + 1) * sizeof(Node*));
			r->n_next++;
			r->next[r->n_next - 1] = t.node;
			Tuple rt;
			rt.token = h;
			rt.node = r;
			return rt;
		}
	} else {
		Tuple rt;
		rt.token = h;
		rt.node = r;
		return rt;
	}

	printf("Parse Error: Token -> %s\n", h->value);
	exit(0);
}

Tuple parse_PowerExpr(Token *h) {
	Node *r = (Node*)malloc(1 * sizeof(Node));
	r->tokens = (char**)malloc(1 * sizeof(char*));
	r->n_tokens = 0;
	r->next = (Node**)malloc(1 * sizeof(Node*));
	r->n_next = 0;
	r->name = (char*)malloc(9 * sizeof(char));
	s_move(r->name, "PowerExpr");

	Tuple t = parse_UnaryExpr(h);
	h = t.token;
	r->next = realloc(r->next, (r->n_next + 1) * sizeof(Node*));
	r->n_next++;
	r->next[r->n_next - 1] = t.node;

	if(lookahead(h) == 26) {
		r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
		r->n_tokens++;
		r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
		s_move(r->tokens[r->n_tokens - 1], h->value);
		h = match_token(h, 26);

		if(lookahead(h) == 24 || lookahead(h) == 25 || lookahead(h) == 36 || lookahead(h) == 37 || lookahead(h) == 35 || lookahead(h) == 38 || lookahead(h) == 39 || lookahead(h) == 5 || lookahead(h) == 27) {
			Tuple t = parse_PowerExpr(h);
			h = t.token;
			r->next = realloc(r->next, (r->n_next + 1) * sizeof(Node*));
			r->n_next++;
			r->next[r->n_next - 1] = t.node;
			Tuple rt;
			rt.token = h;
			rt.node = r;
			return rt;
		}
	} else {
		Tuple rt;
		rt.token = h;
		rt.node = r;
		return rt;
	}

	printf("Parse Error: Token -> %s\n", h->value);
	exit(0);
}

Tuple parse_UnaryExpr(Token *h) {
	Node *r = (Node*)malloc(1 * sizeof(Node));
	r->tokens = (char**)malloc(1 * sizeof(char*));
	r->n_tokens = 0;
	r->next = (Node**)malloc(1 * sizeof(Node*));
	r->n_next = 0;
	r->name = (char*)malloc(9 * sizeof(char));
	s_move(r->name, "UnaryExpr");


	if(lookahead(h) == 24 || lookahead(h) == 25) {
		Tuple t = parse_UNOPERATOR(h);
		h = t.token;
		r->next = realloc(r->next, (r->n_next + 1) * sizeof(Node*));
		r->n_next++;
		r->next[r->n_next - 1] = t.node;
		if(lookahead(h) == 24 || lookahead(h) == 25 || lookahead(h) == 36 || lookahead(h) == 37 || lookahead(h) == 35 || lookahead(h) == 38 || lookahead(h) == 39 || lookahead(h) == 5 || lookahead(h) == 27) {
			Tuple t = parse_UnaryExpr(h);
			h = t.token;
			r->next = realloc(r->next, (r->n_next + 1) * sizeof(Node*));
			r->n_next++;
			r->next[r->n_next - 1] = t.node;
			Tuple rt;
			rt.token = h;
			rt.node = r;
			return rt;
		}
	} else 	if(lookahead(h) == 36 || lookahead(h) == 37 || lookahead(h) == 35 || lookahead(h) == 38 || lookahead(h) == 39 || lookahead(h) == 5 || lookahead(h) == 27) {
		Tuple t = parse_PrimaryExpr(h);
		h = t.token;
		r->next = realloc(r->next, (r->n_next + 1) * sizeof(Node*));
		r->n_next++;
		r->next[r->n_next - 1] = t.node;
		Tuple rt;
		rt.token = h;
		rt.node = r;
		return rt;
	}
	printf("Parse Error: Token -> %s\n", h->value);
	exit(0);
}

Tuple parse_PrimaryExpr(Token *h) {
	Node *r = (Node*)malloc(1 * sizeof(Node));
	r->tokens = (char**)malloc(1 * sizeof(char*));
	r->n_tokens = 0;
	r->next = (Node**)malloc(1 * sizeof(Node*));
	r->n_next = 0;
	r->name = (char*)malloc(11 * sizeof(char));
	s_move(r->name, "PrimaryExpr");


	if(lookahead(h) == 36) {
		r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
		r->n_tokens++;
		r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
		s_move(r->tokens[r->n_tokens - 1], h->value);
		h = match_token(h, 36);

		Tuple rt;
		rt.token = h;
		rt.node = r;
		return rt;
	} else 	if(lookahead(h) == 37) {
		r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
		r->n_tokens++;
		r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
		s_move(r->tokens[r->n_tokens - 1], h->value);
		h = match_token(h, 37);

		Tuple rt;
		rt.token = h;
		rt.node = r;
		return rt;
	} else 	if(lookahead(h) == 35) {
		r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
		r->n_tokens++;
		r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
		s_move(r->tokens[r->n_tokens - 1], h->value);
		h = match_token(h, 35);

		Tuple rt;
		rt.token = h;
		rt.node = r;
		return rt;
	} else 	if(lookahead(h) == 38) {
		r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
		r->n_tokens++;
		r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
		s_move(r->tokens[r->n_tokens - 1], h->value);
		h = match_token(h, 38);

		Tuple rt;
		rt.token = h;
		rt.node = r;
		return rt;
	} else 	if(lookahead(h) == 39) {
		r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
		r->n_tokens++;
		r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
		s_move(r->tokens[r->n_tokens - 1], h->value);
		h = match_token(h, 39);

		Tuple rt;
		rt.token = h;
		rt.node = r;
		return rt;
	} else 	if(lookahead(h) == 5) {
		r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
		r->n_tokens++;
		r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
		s_move(r->tokens[r->n_tokens - 1], h->value);
		h = match_token(h, 5);

		if(lookahead(h) == 39) {
			r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
			r->n_tokens++;
			r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
			s_move(r->tokens[r->n_tokens - 1], h->value);
			h = match_token(h, 39);

			if(lookahead(h) == 27) {
				r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
				r->n_tokens++;
				r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
				s_move(r->tokens[r->n_tokens - 1], h->value);
				h = match_token(h, 27);

				if(lookahead(h) == 24 || lookahead(h) == 25 || lookahead(h) == 36 || lookahead(h) == 37 || lookahead(h) == 35 || lookahead(h) == 38 || lookahead(h) == 39 || lookahead(h) == 5 || lookahead(h) == 27) {
					Tuple t = parse_ArgsCall(h);
					h = t.token;
					r->next = realloc(r->next, (r->n_next + 1) * sizeof(Node*));
					r->n_next++;
					r->next[r->n_next - 1] = t.node;
					if(lookahead(h) == 28) {
						r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
						r->n_tokens++;
						r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
						s_move(r->tokens[r->n_tokens - 1], h->value);
						h = match_token(h, 28);

						Tuple rt;
						rt.token = h;
						rt.node = r;
						return rt;
					}
				}
			}
		}
	} else 	if(lookahead(h) == 27) {
		r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
		r->n_tokens++;
		r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
		s_move(r->tokens[r->n_tokens - 1], h->value);
		h = match_token(h, 27);

		if(lookahead(h) == 24 || lookahead(h) == 25 || lookahead(h) == 36 || lookahead(h) == 37 || lookahead(h) == 35 || lookahead(h) == 38 || lookahead(h) == 39 || lookahead(h) == 5 || lookahead(h) == 27) {
			Tuple t = parse_Expr(h);
			h = t.token;
			r->next = realloc(r->next, (r->n_next + 1) * sizeof(Node*));
			r->n_next++;
			r->next[r->n_next - 1] = t.node;
			if(lookahead(h) == 28) {
				r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
				r->n_tokens++;
				r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
				s_move(r->tokens[r->n_tokens - 1], h->value);
				h = match_token(h, 28);

				Tuple rt;
				rt.token = h;
				rt.node = r;
				return rt;
			}
		}
	}
	printf("Parse Error: Token -> %s\n", h->value);
	exit(0);
}

Tuple parse_ArgsCall(Token *h) {
	Node *r = (Node*)malloc(1 * sizeof(Node));
	r->tokens = (char**)malloc(1 * sizeof(char*));
	r->n_tokens = 0;
	r->next = (Node**)malloc(1 * sizeof(Node*));
	r->n_next = 0;
	r->name = (char*)malloc(8 * sizeof(char));
	s_move(r->name, "ArgsCall");

	Tuple t = parse_Expr(h);
	h = t.token;
	r->next = realloc(r->next, (r->n_next + 1) * sizeof(Node*));
	r->n_next++;
	r->next[r->n_next - 1] = t.node;

	if(lookahead(h) == 29) {
		r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
		r->n_tokens++;
		r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
		s_move(r->tokens[r->n_tokens - 1], h->value);
		h = match_token(h, 29);

		if(lookahead(h) == 24 || lookahead(h) == 25 || lookahead(h) == 36 || lookahead(h) == 37 || lookahead(h) == 35 || lookahead(h) == 38 || lookahead(h) == 39 || lookahead(h) == 5 || lookahead(h) == 27) {
			Tuple t = parse_ArgsCall(h);
			h = t.token;
			r->next = realloc(r->next, (r->n_next + 1) * sizeof(Node*));
			r->n_next++;
			r->next[r->n_next - 1] = t.node;
			Tuple rt;
			rt.token = h;
			rt.node = r;
			return rt;
		}
	} else 	if(lookahead(h) == 30) {
		r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
		r->n_tokens++;
		r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
		s_move(r->tokens[r->n_tokens - 1], h->value);
		h = match_token(h, 30);

		Tuple rt;
		rt.token = h;
		rt.node = r;
		return rt;
	} else {
		Tuple rt;
		rt.token = h;
		rt.node = r;
		return rt;
	}

	printf("Parse Error: Token -> %s\n", h->value);
	exit(0);
}

Tuple parse_Type(Token *h) {
	Node *r = (Node*)malloc(1 * sizeof(Node));
	r->tokens = (char**)malloc(1 * sizeof(char*));
	r->n_tokens = 0;
	r->next = (Node**)malloc(1 * sizeof(Node*));
	r->n_next = 0;
	r->name = (char*)malloc(4 * sizeof(char));
	s_move(r->name, "Type");


	if(lookahead(h) == 9) {
		r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
		r->n_tokens++;
		r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
		s_move(r->tokens[r->n_tokens - 1], h->value);
		h = match_token(h, 9);

		Tuple rt;
		rt.token = h;
		rt.node = r;
		return rt;
	} else 	if(lookahead(h) == 6) {
		r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
		r->n_tokens++;
		r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
		s_move(r->tokens[r->n_tokens - 1], h->value);
		h = match_token(h, 6);

		Tuple rt;
		rt.token = h;
		rt.node = r;
		return rt;
	} else 	if(lookahead(h) == 2) {
		r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
		r->n_tokens++;
		r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
		s_move(r->tokens[r->n_tokens - 1], h->value);
		h = match_token(h, 2);

		Tuple rt;
		rt.token = h;
		rt.node = r;
		return rt;
	} else 	if(lookahead(h) == 7) {
		r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
		r->n_tokens++;
		r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
		s_move(r->tokens[r->n_tokens - 1], h->value);
		h = match_token(h, 7);

		Tuple rt;
		rt.token = h;
		rt.node = r;
		return rt;
	}
	printf("Parse Error: Token -> %s\n", h->value);
	exit(0);
}

Tuple parse_Stmt(Token *h) {
	Node *r = (Node*)malloc(1 * sizeof(Node));
	r->tokens = (char**)malloc(1 * sizeof(char*));
	r->n_tokens = 0;
	r->next = (Node**)malloc(1 * sizeof(Node*));
	r->n_next = 0;
	r->name = (char*)malloc(4 * sizeof(char));
	s_move(r->name, "Stmt");

	Tuple t = parse_StmtOptions(h);
	h = t.token;
	r->next = realloc(r->next, (r->n_next + 1) * sizeof(Node*));
	r->n_next++;
	r->next[r->n_next - 1] = t.node;

	if(lookahead(h) == 9 || lookahead(h) == 6 || lookahead(h) == 2 || lookahead(h) == 7 || lookahead(h) == 39 || lookahead(h) == 0 || lookahead(h) == 17 || lookahead(h) == 3 || lookahead(h) == 1) {
		Tuple t = parse_Stmt(h);
		h = t.token;
		r->next = realloc(r->next, (r->n_next + 1) * sizeof(Node*));
		r->n_next++;
		r->next[r->n_next - 1] = t.node;
		Tuple rt;
		rt.token = h;
		rt.node = r;
		return rt;
	} else {
		Tuple rt;
		rt.token = h;
		rt.node = r;
		return rt;
	}

	printf("Parse Error: Token -> %s\n", h->value);
	exit(0);
}

Tuple parse_StmtOptions(Token *h) {
	Node *r = (Node*)malloc(1 * sizeof(Node));
	r->tokens = (char**)malloc(1 * sizeof(char*));
	r->n_tokens = 0;
	r->next = (Node**)malloc(1 * sizeof(Node*));
	r->n_next = 0;
	r->name = (char*)malloc(11 * sizeof(char));
	s_move(r->name, "StmtOptions");


	if(lookahead(h) == 9 || lookahead(h) == 6 || lookahead(h) == 2 || lookahead(h) == 7) {
		Tuple t = parse_DeclareStmt(h);
		h = t.token;
		r->next = realloc(r->next, (r->n_next + 1) * sizeof(Node*));
		r->n_next++;
		r->next[r->n_next - 1] = t.node;
		Tuple rt;
		rt.token = h;
		rt.node = r;
		return rt;
	} else 	if(lookahead(h) == 39) {
		Tuple t = parse_AssignStmt(h);
		h = t.token;
		r->next = realloc(r->next, (r->n_next + 1) * sizeof(Node*));
		r->n_next++;
		r->next[r->n_next - 1] = t.node;
		Tuple rt;
		rt.token = h;
		rt.node = r;
		return rt;
	} else 	if(lookahead(h) == 0) {
		Tuple t = parse_PrintStmt(h);
		h = t.token;
		r->next = realloc(r->next, (r->n_next + 1) * sizeof(Node*));
		r->n_next++;
		r->next[r->n_next - 1] = t.node;
		Tuple rt;
		rt.token = h;
		rt.node = r;
		return rt;
	} else 	if(lookahead(h) == 17) {
		Tuple t = parse_IfStmt(h);
		h = t.token;
		r->next = realloc(r->next, (r->n_next + 1) * sizeof(Node*));
		r->n_next++;
		r->next[r->n_next - 1] = t.node;
		Tuple rt;
		rt.token = h;
		rt.node = r;
		return rt;
	} else 	if(lookahead(h) == 3) {
		Tuple t = parse_WhileStmt(h);
		h = t.token;
		r->next = realloc(r->next, (r->n_next + 1) * sizeof(Node*));
		r->n_next++;
		r->next[r->n_next - 1] = t.node;
		Tuple rt;
		rt.token = h;
		rt.node = r;
		return rt;
	} else 	if(lookahead(h) == 1) {
		Tuple t = parse_ReturnStmt(h);
		h = t.token;
		r->next = realloc(r->next, (r->n_next + 1) * sizeof(Node*));
		r->n_next++;
		r->next[r->n_next - 1] = t.node;
		Tuple rt;
		rt.token = h;
		rt.node = r;
		return rt;
	}
	printf("Parse Error: Token -> %s\n", h->value);
	exit(0);
}

Tuple parse_DeclareStmt(Token *h) {
	Node *r = (Node*)malloc(1 * sizeof(Node));
	r->tokens = (char**)malloc(1 * sizeof(char*));
	r->n_tokens = 0;
	r->next = (Node**)malloc(1 * sizeof(Node*));
	r->n_next = 0;
	r->name = (char*)malloc(11 * sizeof(char));
	s_move(r->name, "DeclareStmt");

	Tuple t = parse_Type(h);
	h = t.token;
	r->next = realloc(r->next, (r->n_next + 1) * sizeof(Node*));
	r->n_next++;
	r->next[r->n_next - 1] = t.node;

	if(lookahead(h) == 39) {
		r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
		r->n_tokens++;
		r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
		s_move(r->tokens[r->n_tokens - 1], h->value);
		h = match_token(h, 39);

		if(lookahead(h) == 31) {
			r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
			r->n_tokens++;
			r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
			s_move(r->tokens[r->n_tokens - 1], h->value);
			h = match_token(h, 31);

			Tuple rt;
			rt.token = h;
			rt.node = r;
			return rt;
		}
	} else {
		Tuple rt;
		rt.token = h;
		rt.node = r;
		return rt;
	}

	printf("Parse Error: Token -> %s\n", h->value);
	exit(0);
}

Tuple parse_AssignStmt(Token *h) {
	Node *r = (Node*)malloc(1 * sizeof(Node));
	r->tokens = (char**)malloc(1 * sizeof(char*));
	r->n_tokens = 0;
	r->next = (Node**)malloc(1 * sizeof(Node*));
	r->n_next = 0;
	r->name = (char*)malloc(10 * sizeof(char));
	s_move(r->name, "AssignStmt");


	if(lookahead(h) == 39) {
		r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
		r->n_tokens++;
		r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
		s_move(r->tokens[r->n_tokens - 1], h->value);
		h = match_token(h, 39);

		if(lookahead(h) == 32) {
			r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
			r->n_tokens++;
			r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
			s_move(r->tokens[r->n_tokens - 1], h->value);
			h = match_token(h, 32);

			if(lookahead(h) == 24 || lookahead(h) == 25 || lookahead(h) == 36 || lookahead(h) == 37 || lookahead(h) == 35 || lookahead(h) == 38 || lookahead(h) == 39 || lookahead(h) == 5 || lookahead(h) == 27) {
				Tuple t = parse_Expr(h);
				h = t.token;
				r->next = realloc(r->next, (r->n_next + 1) * sizeof(Node*));
				r->n_next++;
				r->next[r->n_next - 1] = t.node;
				if(lookahead(h) == 31) {
					r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
					r->n_tokens++;
					r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
					s_move(r->tokens[r->n_tokens - 1], h->value);
					h = match_token(h, 31);

					Tuple rt;
					rt.token = h;
					rt.node = r;
					return rt;
				}
			}
		}
	}
	printf("Parse Error: Token -> %s\n", h->value);
	exit(0);
}

Tuple parse_PrintStmt(Token *h) {
	Node *r = (Node*)malloc(1 * sizeof(Node));
	r->tokens = (char**)malloc(1 * sizeof(char*));
	r->n_tokens = 0;
	r->next = (Node**)malloc(1 * sizeof(Node*));
	r->n_next = 0;
	r->name = (char*)malloc(9 * sizeof(char));
	s_move(r->name, "PrintStmt");


	if(lookahead(h) == 0) {
		r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
		r->n_tokens++;
		r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
		s_move(r->tokens[r->n_tokens - 1], h->value);
		h = match_token(h, 0);

		if(lookahead(h) == 27) {
			r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
			r->n_tokens++;
			r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
			s_move(r->tokens[r->n_tokens - 1], h->value);
			h = match_token(h, 27);

			if(lookahead(h) == 24 || lookahead(h) == 25 || lookahead(h) == 36 || lookahead(h) == 37 || lookahead(h) == 35 || lookahead(h) == 38 || lookahead(h) == 39 || lookahead(h) == 5 || lookahead(h) == 27) {
				Tuple t = parse_Expr(h);
				h = t.token;
				r->next = realloc(r->next, (r->n_next + 1) * sizeof(Node*));
				r->n_next++;
				r->next[r->n_next - 1] = t.node;
				if(lookahead(h) == 28) {
					r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
					r->n_tokens++;
					r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
					s_move(r->tokens[r->n_tokens - 1], h->value);
					h = match_token(h, 28);

					if(lookahead(h) == 31) {
						r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
						r->n_tokens++;
						r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
						s_move(r->tokens[r->n_tokens - 1], h->value);
						h = match_token(h, 31);

						Tuple rt;
						rt.token = h;
						rt.node = r;
						return rt;
					}
				}
			}
		}
	}
	printf("Parse Error: Token -> %s\n", h->value);
	exit(0);
}

Tuple parse_IfStmt(Token *h) {
	Node *r = (Node*)malloc(1 * sizeof(Node));
	r->tokens = (char**)malloc(1 * sizeof(char*));
	r->n_tokens = 0;
	r->next = (Node**)malloc(1 * sizeof(Node*));
	r->n_next = 0;
	r->name = (char*)malloc(6 * sizeof(char));
	s_move(r->name, "IfStmt");


	if(lookahead(h) == 17) {
		r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
		r->n_tokens++;
		r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
		s_move(r->tokens[r->n_tokens - 1], h->value);
		h = match_token(h, 17);

		if(lookahead(h) == 27) {
			r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
			r->n_tokens++;
			r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
			s_move(r->tokens[r->n_tokens - 1], h->value);
			h = match_token(h, 27);

			if(lookahead(h) == 24 || lookahead(h) == 25 || lookahead(h) == 36 || lookahead(h) == 37 || lookahead(h) == 35 || lookahead(h) == 38 || lookahead(h) == 39 || lookahead(h) == 5 || lookahead(h) == 27) {
				Tuple t = parse_Expr(h);
				h = t.token;
				r->next = realloc(r->next, (r->n_next + 1) * sizeof(Node*));
				r->n_next++;
				r->next[r->n_next - 1] = t.node;
				if(lookahead(h) == 28) {
					r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
					r->n_tokens++;
					r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
					s_move(r->tokens[r->n_tokens - 1], h->value);
					h = match_token(h, 28);

					if(lookahead(h) == 33) {
						r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
						r->n_tokens++;
						r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
						s_move(r->tokens[r->n_tokens - 1], h->value);
						h = match_token(h, 33);

						if(lookahead(h) == 9 || lookahead(h) == 6 || lookahead(h) == 2 || lookahead(h) == 7 || lookahead(h) == 39 || lookahead(h) == 0 || lookahead(h) == 17 || lookahead(h) == 3 || lookahead(h) == 1) {
							Tuple t = parse_Stmt(h);
							h = t.token;
							r->next = realloc(r->next, (r->n_next + 1) * sizeof(Node*));
							r->n_next++;
							r->next[r->n_next - 1] = t.node;
							if(lookahead(h) == 34) {
								r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
								r->n_tokens++;
								r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
								s_move(r->tokens[r->n_tokens - 1], h->value);
								h = match_token(h, 34);

								if(lookahead(h) == 8 || lookahead(h) == 31) {
									Tuple t = parse_ElseBranch(h);
									h = t.token;
									r->next = realloc(r->next, (r->n_next + 1) * sizeof(Node*));
									r->n_next++;
									r->next[r->n_next - 1] = t.node;
									Tuple rt;
									rt.token = h;
									rt.node = r;
									return rt;
								}
							}
						}
					}
				}
			}
		}
	}
	printf("Parse Error: Token -> %s\n", h->value);
	exit(0);
}

Tuple parse_ElseBranch(Token *h) {
	Node *r = (Node*)malloc(1 * sizeof(Node));
	r->tokens = (char**)malloc(1 * sizeof(char*));
	r->n_tokens = 0;
	r->next = (Node**)malloc(1 * sizeof(Node*));
	r->n_next = 0;
	r->name = (char*)malloc(10 * sizeof(char));
	s_move(r->name, "ElseBranch");


	if(lookahead(h) == 8) {
		r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
		r->n_tokens++;
		r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
		s_move(r->tokens[r->n_tokens - 1], h->value);
		h = match_token(h, 8);

		if(lookahead(h) == 33) {
			r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
			r->n_tokens++;
			r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
			s_move(r->tokens[r->n_tokens - 1], h->value);
			h = match_token(h, 33);

			if(lookahead(h) == 9 || lookahead(h) == 6 || lookahead(h) == 2 || lookahead(h) == 7 || lookahead(h) == 39 || lookahead(h) == 0 || lookahead(h) == 17 || lookahead(h) == 3 || lookahead(h) == 1) {
				Tuple t = parse_Stmt(h);
				h = t.token;
				r->next = realloc(r->next, (r->n_next + 1) * sizeof(Node*));
				r->n_next++;
				r->next[r->n_next - 1] = t.node;
				if(lookahead(h) == 34) {
					r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
					r->n_tokens++;
					r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
					s_move(r->tokens[r->n_tokens - 1], h->value);
					h = match_token(h, 34);

					Tuple rt;
					rt.token = h;
					rt.node = r;
					return rt;
				}
			}
		}
	} else 	if(lookahead(h) == 31) {
		r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
		r->n_tokens++;
		r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
		s_move(r->tokens[r->n_tokens - 1], h->value);
		h = match_token(h, 31);

		Tuple rt;
		rt.token = h;
		rt.node = r;
		return rt;
	}
	printf("Parse Error: Token -> %s\n", h->value);
	exit(0);
}

Tuple parse_WhileStmt(Token *h) {
	Node *r = (Node*)malloc(1 * sizeof(Node));
	r->tokens = (char**)malloc(1 * sizeof(char*));
	r->n_tokens = 0;
	r->next = (Node**)malloc(1 * sizeof(Node*));
	r->n_next = 0;
	r->name = (char*)malloc(9 * sizeof(char));
	s_move(r->name, "WhileStmt");


	if(lookahead(h) == 3) {
		r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
		r->n_tokens++;
		r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
		s_move(r->tokens[r->n_tokens - 1], h->value);
		h = match_token(h, 3);

		if(lookahead(h) == 27) {
			r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
			r->n_tokens++;
			r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
			s_move(r->tokens[r->n_tokens - 1], h->value);
			h = match_token(h, 27);

			if(lookahead(h) == 24 || lookahead(h) == 25 || lookahead(h) == 36 || lookahead(h) == 37 || lookahead(h) == 35 || lookahead(h) == 38 || lookahead(h) == 39 || lookahead(h) == 5 || lookahead(h) == 27) {
				Tuple t = parse_Expr(h);
				h = t.token;
				r->next = realloc(r->next, (r->n_next + 1) * sizeof(Node*));
				r->n_next++;
				r->next[r->n_next - 1] = t.node;
				if(lookahead(h) == 28) {
					r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
					r->n_tokens++;
					r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
					s_move(r->tokens[r->n_tokens - 1], h->value);
					h = match_token(h, 28);

					if(lookahead(h) == 33) {
						r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
						r->n_tokens++;
						r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
						s_move(r->tokens[r->n_tokens - 1], h->value);
						h = match_token(h, 33);

						if(lookahead(h) == 9 || lookahead(h) == 6 || lookahead(h) == 2 || lookahead(h) == 7 || lookahead(h) == 39 || lookahead(h) == 0 || lookahead(h) == 17 || lookahead(h) == 3 || lookahead(h) == 1) {
							Tuple t = parse_Stmt(h);
							h = t.token;
							r->next = realloc(r->next, (r->n_next + 1) * sizeof(Node*));
							r->n_next++;
							r->next[r->n_next - 1] = t.node;
							if(lookahead(h) == 34) {
								r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
								r->n_tokens++;
								r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
								s_move(r->tokens[r->n_tokens - 1], h->value);
								h = match_token(h, 34);

								if(lookahead(h) == 31) {
									r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
									r->n_tokens++;
									r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
									s_move(r->tokens[r->n_tokens - 1], h->value);
									h = match_token(h, 31);

									Tuple rt;
									rt.token = h;
									rt.node = r;
									return rt;
								}
							}
						}
					}
				}
			}
		}
	}
	printf("Parse Error: Token -> %s\n", h->value);
	exit(0);
}

Tuple parse_ReturnStmt(Token *h) {
	Node *r = (Node*)malloc(1 * sizeof(Node));
	r->tokens = (char**)malloc(1 * sizeof(char*));
	r->n_tokens = 0;
	r->next = (Node**)malloc(1 * sizeof(Node*));
	r->n_next = 0;
	r->name = (char*)malloc(10 * sizeof(char));
	s_move(r->name, "ReturnStmt");


	if(lookahead(h) == 1) {
		r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
		r->n_tokens++;
		r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
		s_move(r->tokens[r->n_tokens - 1], h->value);
		h = match_token(h, 1);

		if(lookahead(h) == 24 || lookahead(h) == 25 || lookahead(h) == 36 || lookahead(h) == 37 || lookahead(h) == 35 || lookahead(h) == 38 || lookahead(h) == 39 || lookahead(h) == 5 || lookahead(h) == 27) {
			Tuple t = parse_Expr(h);
			h = t.token;
			r->next = realloc(r->next, (r->n_next + 1) * sizeof(Node*));
			r->n_next++;
			r->next[r->n_next - 1] = t.node;
			if(lookahead(h) == 31) {
				r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
				r->n_tokens++;
				r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
				s_move(r->tokens[r->n_tokens - 1], h->value);
				h = match_token(h, 31);

				Tuple rt;
				rt.token = h;
				rt.node = r;
				return rt;
			}
		}
	}
	printf("Parse Error: Token -> %s\n", h->value);
	exit(0);
}

Tuple parse_Super(Token *h) {
	Node *r = (Node*)malloc(1 * sizeof(Node));
	r->tokens = (char**)malloc(1 * sizeof(char*));
	r->n_tokens = 0;
	r->next = (Node**)malloc(1 * sizeof(Node*));
	r->n_next = 0;
	r->name = (char*)malloc(5 * sizeof(char));
	s_move(r->name, "Super");

	Tuple t = parse_SuperOptions(h);
	h = t.token;
	r->next = realloc(r->next, (r->n_next + 1) * sizeof(Node*));
	r->n_next++;
	r->next[r->n_next - 1] = t.node;

	if(lookahead(h) == 4 || lookahead(h) == 9 || lookahead(h) == 6 || lookahead(h) == 2 || lookahead(h) == 7 || lookahead(h) == 39 || lookahead(h) == 0 || lookahead(h) == 17 || lookahead(h) == 3 || lookahead(h) == 1) {
		Tuple t = parse_Super(h);
		h = t.token;
		r->next = realloc(r->next, (r->n_next + 1) * sizeof(Node*));
		r->n_next++;
		r->next[r->n_next - 1] = t.node;
		Tuple rt;
		rt.token = h;
		rt.node = r;
		return rt;
	} else 	if(lookahead(h) == 10) {
		r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
		r->n_tokens++;
		r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
		s_move(r->tokens[r->n_tokens - 1], h->value);
		h = match_token(h, 10);

		Tuple rt;
		rt.token = h;
		rt.node = r;
		return rt;
	} else {
		Tuple rt;
		rt.token = h;
		rt.node = r;
		return rt;
	}

	printf("Parse Error: Token -> %s\n", h->value);
	exit(0);
}

Tuple parse_SuperOptions(Token *h) {
	Node *r = (Node*)malloc(1 * sizeof(Node));
	r->tokens = (char**)malloc(1 * sizeof(char*));
	r->n_tokens = 0;
	r->next = (Node**)malloc(1 * sizeof(Node*));
	r->n_next = 0;
	r->name = (char*)malloc(12 * sizeof(char));
	s_move(r->name, "SuperOptions");


	if(lookahead(h) == 4) {
		Tuple t = parse_Function(h);
		h = t.token;
		r->next = realloc(r->next, (r->n_next + 1) * sizeof(Node*));
		r->n_next++;
		r->next[r->n_next - 1] = t.node;
		Tuple rt;
		rt.token = h;
		rt.node = r;
		return rt;
	} else 	if(lookahead(h) == 9 || lookahead(h) == 6 || lookahead(h) == 2 || lookahead(h) == 7 || lookahead(h) == 39 || lookahead(h) == 0 || lookahead(h) == 17 || lookahead(h) == 3 || lookahead(h) == 1) {
		Tuple t = parse_Stmt(h);
		h = t.token;
		r->next = realloc(r->next, (r->n_next + 1) * sizeof(Node*));
		r->n_next++;
		r->next[r->n_next - 1] = t.node;
		Tuple rt;
		rt.token = h;
		rt.node = r;
		return rt;
	}
	printf("Parse Error: Token -> %s\n", h->value);
	exit(0);
}

Tuple parse_Function(Token *h) {
	Node *r = (Node*)malloc(1 * sizeof(Node));
	r->tokens = (char**)malloc(1 * sizeof(char*));
	r->n_tokens = 0;
	r->next = (Node**)malloc(1 * sizeof(Node*));
	r->n_next = 0;
	r->name = (char*)malloc(8 * sizeof(char));
	s_move(r->name, "Function");


	if(lookahead(h) == 4) {
		r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
		r->n_tokens++;
		r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
		s_move(r->tokens[r->n_tokens - 1], h->value);
		h = match_token(h, 4);

		if(lookahead(h) == 9 || lookahead(h) == 6 || lookahead(h) == 2 || lookahead(h) == 7) {
			Tuple t = parse_Type(h);
			h = t.token;
			r->next = realloc(r->next, (r->n_next + 1) * sizeof(Node*));
			r->n_next++;
			r->next[r->n_next - 1] = t.node;
			if(lookahead(h) == 39) {
				r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
				r->n_tokens++;
				r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
				s_move(r->tokens[r->n_tokens - 1], h->value);
				h = match_token(h, 39);

				if(lookahead(h) == 27) {
					r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
					r->n_tokens++;
					r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
					s_move(r->tokens[r->n_tokens - 1], h->value);
					h = match_token(h, 27);

					if(lookahead(h) == 9 || lookahead(h) == 6 || lookahead(h) == 2 || lookahead(h) == 7) {
						Tuple t = parse_Args(h);
						h = t.token;
						r->next = realloc(r->next, (r->n_next + 1) * sizeof(Node*));
						r->n_next++;
						r->next[r->n_next - 1] = t.node;
						if(lookahead(h) == 28) {
							r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
							r->n_tokens++;
							r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
							s_move(r->tokens[r->n_tokens - 1], h->value);
							h = match_token(h, 28);

							if(lookahead(h) == 33) {
								r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
								r->n_tokens++;
								r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
								s_move(r->tokens[r->n_tokens - 1], h->value);
								h = match_token(h, 33);

								if(lookahead(h) == 9 || lookahead(h) == 6 || lookahead(h) == 2 || lookahead(h) == 7 || lookahead(h) == 39 || lookahead(h) == 0 || lookahead(h) == 17 || lookahead(h) == 3 || lookahead(h) == 1) {
									Tuple t = parse_Stmt(h);
									h = t.token;
									r->next = realloc(r->next, (r->n_next + 1) * sizeof(Node*));
									r->n_next++;
									r->next[r->n_next - 1] = t.node;
									if(lookahead(h) == 34) {
										r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
										r->n_tokens++;
										r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
										s_move(r->tokens[r->n_tokens - 1], h->value);
										h = match_token(h, 34);

										Tuple rt;
										rt.token = h;
										rt.node = r;
										return rt;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	printf("Parse Error: Token -> %s\n", h->value);
	exit(0);
}

Tuple parse_Args(Token *h) {
	Node *r = (Node*)malloc(1 * sizeof(Node));
	r->tokens = (char**)malloc(1 * sizeof(char*));
	r->n_tokens = 0;
	r->next = (Node**)malloc(1 * sizeof(Node*));
	r->n_next = 0;
	r->name = (char*)malloc(4 * sizeof(char));
	s_move(r->name, "Args");

	Tuple t = parse_Arg(h);
	h = t.token;
	r->next = realloc(r->next, (r->n_next + 1) * sizeof(Node*));
	r->n_next++;
	r->next[r->n_next - 1] = t.node;

	if(lookahead(h) == 29) {
		r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
		r->n_tokens++;
		r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
		s_move(r->tokens[r->n_tokens - 1], h->value);
		h = match_token(h, 29);

		if(lookahead(h) == 9 || lookahead(h) == 6 || lookahead(h) == 2 || lookahead(h) == 7) {
			Tuple t = parse_Args(h);
			h = t.token;
			r->next = realloc(r->next, (r->n_next + 1) * sizeof(Node*));
			r->n_next++;
			r->next[r->n_next - 1] = t.node;
			Tuple rt;
			rt.token = h;
			rt.node = r;
			return rt;
		}
	} else {
		Tuple rt;
		rt.token = h;
		rt.node = r;
		return rt;
	}

	printf("Parse Error: Token -> %s\n", h->value);
	exit(0);
}

Tuple parse_Arg(Token *h) {
	Node *r = (Node*)malloc(1 * sizeof(Node));
	r->tokens = (char**)malloc(1 * sizeof(char*));
	r->n_tokens = 0;
	r->next = (Node**)malloc(1 * sizeof(Node*));
	r->n_next = 0;
	r->name = (char*)malloc(3 * sizeof(char));
	s_move(r->name, "Arg");

	Tuple t = parse_Type(h);
	h = t.token;
	r->next = realloc(r->next, (r->n_next + 1) * sizeof(Node*));
	r->n_next++;
	r->next[r->n_next - 1] = t.node;

	if(lookahead(h) == 39) {
		r->tokens = realloc(r->tokens, (r->n_tokens + 1) * sizeof(char*));
		r->n_tokens++;
		r->tokens[r->n_tokens - 1] = (char*)malloc(strlen(h->value) * sizeof(char));
		s_move(r->tokens[r->n_tokens - 1], h->value);
		h = match_token(h, 39);

		Tuple rt;
		rt.token = h;
		rt.node = r;
		return rt;
	} else {
		Tuple rt;
		rt.token = h;
		rt.node = r;
		return rt;
	}

	printf("Parse Error: Token -> %s\n", h->value);
	exit(0);
}

