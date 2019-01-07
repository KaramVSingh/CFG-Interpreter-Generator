#if !defined(PARSE_H)
#define PARSE_H

#include "tokenize.h"

typedef struct Node {
    char *name;                     // name of node instruction (identifier)
    char **tokens;                  // tokens captured by node
    int n_tokens;                   // number of tokens captured by node
    struct Node **next;             // children of node in AST
    int n_next;                     // number of children in node
} Node;

typedef struct Tuple {
    Node *node;
    Token *token;
} Tuple;

int lookahead(Token *h);
Token* match_token(Token *h, int v);
Node* parse(Token *h);
Tuple parse_EQOPERATOR(Token *h);
Tuple parse_REOPERATOR(Token *h);
Tuple parse_ADOPERATOR(Token *h);
Tuple parse_MULOPERATOR(Token *h);
Tuple parse_UNOPERATOR(Token *h);
Tuple parse_Expr(Token *h);
Tuple parse_OrExpr(Token *h);
Tuple parse_AndExpr(Token *h);
Tuple parse_EqualityExpr(Token *h);
Tuple parse_RelationalExpr(Token *h);
Tuple parse_AdditiveExpr(Token *h);
Tuple parse_MultiplicativeExpr(Token *h);
Tuple parse_PowerExpr(Token *h);
Tuple parse_UnaryExpr(Token *h);
Tuple parse_PrimaryExpr(Token *h);
Tuple parse_ArgsCall(Token *h);
Tuple parse_Type(Token *h);
Tuple parse_Stmt(Token *h);
Tuple parse_StmtOptions(Token *h);
Tuple parse_DeclareStmt(Token *h);
Tuple parse_AssignStmt(Token *h);
Tuple parse_PrintStmt(Token *h);
Tuple parse_IfStmt(Token *h);
Tuple parse_ElseBranch(Token *h);
Tuple parse_WhileStmt(Token *h);
Tuple parse_ReturnStmt(Token *h);
Tuple parse_Super(Token *h);
Tuple parse_SuperOptions(Token *h);
Tuple parse_Function(Token *h);
Tuple parse_Args(Token *h);
Tuple parse_Arg(Token *h);

#endif