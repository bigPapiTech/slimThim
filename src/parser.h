#ifndef LEX_H
#include "lex.h"
#endif
#ifndef TOKEN_H
#include "token.h"
#endif
#ifndef PARSER_H 
#define PARSER_H
/*
enum ExprType {
  LITERAL,
  UNARY,
  BINARY,
  GROUPING
};

typedef struct Expr
{
    struct Expr *left;
    enum ExprType type;
    Token *operator;
    struct Expr *right;
} Expr;

struct Expr *expression(Token**);
//void treePrint(Expr *root, int level);
void generateCode(Expr*);
//const char* getOperatorTypeName(enum TokenType type);
const char* getExprTypeName(int type);
*/
#endif
