#ifndef LEX_H
#include "lex.h"
#endif
#ifndef TOKEN_H
#include "token.h"
#endif
#ifndef PARSER_H 
#define PARSER_H


typedef struct Expr
{
    struct Expr *left;
    struct Expr *right;
    Token *token;
} Expr;

Expr *parse(Expr*, Token*);
/*
enum ExprType {
  LITERAL,
  UNARY,
  BINARY,
  GROUPING
};


//void treePrint(Expr *root, int level);
void generateCode(Expr*);
//const char* getOperatorTypeName(enum TokenType type);
const char* getExprTypeName(int type);
*/
#endif
