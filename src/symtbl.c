#include <stdlib.h>
#include <stdio.h>
#include "symtbl.h"
#include "main.h"
#define SYMTBLSIZE 5
int sym_tbl_size = SYMTBLSIZE;


int 
insert_sym_tbl(sym_row *sym_tbl, int id, char *attribute, int length){

  
   if(id > sym_tbl_size){
    sym_tbl_size *= 2;
    sym_tbl = realloc(sym_tbl, sym_tbl_size *sizeof(sym_row));
    if(sym_tbl == NULL){
      printf("Mem Error SYM_TBL");
      exit(-1);
    }
  }

  sym_row r = {.id = id, .attribute = attribute};
  sym_tbl[id] = r;
  return 0;
}
