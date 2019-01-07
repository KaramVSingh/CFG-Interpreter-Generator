#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokenize.h"
#include "parse.h"

int main(int argc, char *argv[]) {
    Token* h = tokenize(argv[argc - 1]);
    Node* n = parse(h);
    n = parse_clean(n);
}