#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helper.h"
#include "parser.h"
#include "lex.h"
#include "symtbl.h"
#include "debugtbl.h"
#define DEBUGTBLSIZE 5
#define SYMTBLSIZE 5


int main(int argc, char *argv[]) {

  checkInput(argc);
  
  /* LEXICAL ANALYSIS */ 

  // Init 
  fp = fopen(argv[1], "r");
  if (fp == NULL){
    die("Could not read source file");
  }

  init_lex(fp);

  sym_row *sym_tbl;
  sym_tbl = malloc(SYMTBLSIZE*sizeof(sym_row));
  if(sym_tbl == NULL){
    printf("Mem Error creating symtbl");
    exit(-1);
  }

  debug_row *debug_tbl;
  debug_tbl = malloc(DEBUGTBLSIZE*sizeof(debug_row));
  if(debug_tbl == NULL){
    printf("Mem Error creating debugtbl");
    exit(-1);
  }

  Expr *e = NULL;

  for(int i = get_next_token(); i != -1; i = get_next_token()){
    insert_sym_tbl(sym_tbl, SYM_TBL_ID, *ATTRIBUTE, SYM_LENGTH);
    insert_debug_tbl(debug_tbl, DEBUG_TBL_ID, CC, WC, LC);
    printf("Token: %s, CC: %d WC: %d LC: %d, Attribute: %s\n", get_token_name(i), debug_tbl[DEBUG_TBL_ID].cc, debug_tbl[DEBUG_TBL_ID].wc , debug_tbl[DEBUG_TBL_ID].lc, (i == T_ID) ? sym_tbl[SYM_TBL_ID].attribute: "" );
    printf("\n\n");

    e = parse(e, newToken(T_ID, &sym_tbl[SYM_TBL_ID], &debug_tbl[DEBUG_TBL_ID]));

  }
  return 0;
}
