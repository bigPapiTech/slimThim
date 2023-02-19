#ifndef TOKEN_H
#include "token.h"
#endif
#ifndef SYMTBL_H
#include "symtbl.h"
#endif
#ifndef LEX_H
#define LEX_H
#define BUFSIZE 5

extern FILE *fp;

// Buffers
extern char BUF0[BUFSIZE];
extern char BUF1[BUFSIZE];
extern char **ATTRIBUTE;
extern int ACTIVE_F_BUF;
extern int ACTIVE_LB_BUF;
extern char *FORWARD;
extern char *LEXEME_BEGIN;

// Debug
extern int CC;
extern int LC;
extern int WC;

// Token State
extern int SYM_TBL_ID;
extern int DEBUG_TBL_ID;
extern int SYM_STATE;
extern int SYM_LENGTH;
extern char **ATTRIBUTE;

void
init_lex();

//Token*
int
get_next_token();

#endif
