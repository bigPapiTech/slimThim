#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helper.h"
#include "parser.h"
#include "lex.h"
#include "symtbl.h"
#define SYMTBLSIZE 5

//sym_row **SYM_TBL = NULL;

int main(int argc, char *argv[]) {

  checkInput(argc);
  
  /* LEXICAL ANALYSIS */ 

  // Init 
  fp = fopen(argv[1], "r");
  if (fp == NULL){
    die("Could not read source file");
  }

  ACTIVE_F_BUF = 1;
  ACTIVE_LB_BUF = 1;
  init_lex(fp);


  sym_row *sym_tbl;
  sym_tbl = malloc(SYMTBLSIZE*sizeof(sym_row));
  if(sym_tbl == NULL){
    printf("Mem Error creating symtbl");
    exit(-1);
  }
  for(int i = get_next_token(); i != -1; i = get_next_token()){
    insert_sym_tbl(sym_tbl, SYM_TBL_ID, *ATTRIBUTE, SYM_LENGTH);
    printf("Token: %s, Attribute: %s\n", get_token_name(i), (i == T_ID) ? sym_tbl[SYM_TBL_ID].attribute: "" );
    printf("SYM_ID: %d ", i);
    printf("SYM_STATE: %d ",SYM_STATE);
    printf("SYM_LENGTH: %d ", SYM_LENGTH);
    printf("\n");
    printf("CC: %d ", CC-SYM_LENGTH);
    printf("WC: %d ", WC);
    printf("LC: %d ", LC);
    printf("\n\n");
  }
  return 0;
}
