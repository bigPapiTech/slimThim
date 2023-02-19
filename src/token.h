//#ifndef DEBUGROW_H
//#include "debugrow.h"
//#endif
#ifndef SYMTBL_H
#include "symtbl.h"
#endif
#ifndef DEBUGTBL_H
#include "debugtbl.h"
#endif

#ifndef TOKEN_H
#define TOKEN_H

// Used by the parser
typedef struct Token {
  int name;
  sym_row *symbol;
  debug_row *debug;
} Token;


Token *newToken(int, sym_row*, debug_row*);
const char *get_token_name(int token);

/*

Token *rewindTokenList(Token *t);     // lex
void destroyToken(Token*);
void destroyTokens(Token*);
void printTokens(Token*);
*/

enum TokenName {
  // Keywords
  T_NEW_LINE,
  T_WHITE_SPACE,
	T_SEMICOLON, 
  T_IF,
  T_THEN,
	T_ELSE, 
	T_CLASS, 
	T_FALSE, 
	T_FUN, 
	T_FOR, 
	T_NIL, 
  T_PRINT, 
	T_RETURN, 
	T_SUPER, 
	T_THIS, 
	T_TRUE, 
	T_VAR, 
	T_WHILE,
	T_LEFT_PAREN, 
	T_RIGHT_PAREN, 
	T_LEFT_BRACE, 
	T_RIGHT_BRACE,
  T_COMMA, 
	T_DOT, 
	T_MINUS, 
	T_PLUS, 
  T_SLASH, 
	T_STAR,
  // Grouping
  T_GROUPING,

  // Operators
  //T_RELOP,
  T_BANG, 
	T_BANG_EQUAL,
  T_EQUAL, 
	T_EQUAL_EQUAL,
  T_GREATER, 
	T_GREATER_EQUAL,
  T_LESS, 
	T_LESS_EQUAL,
  T_OR,
  T_AND,
  
  // Literals.
  T_ID,
  T_NUMBER,

};


#endif
