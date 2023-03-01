#include <stdlib.h>
#include <stdio.h>
#include "debugtbl.h"
#include "main.h"
#define DEBUGTBLSIZE 5
int debug_tbl_size = DEBUGTBLSIZE;


int
insert_debug_tbl(debug_row *debug_tbl, int id, int cc, int wc, int lc){


   if(id > debug_tbl_size){
    debug_tbl_size *= 2;
    debug_tbl = realloc(debug_tbl, debug_tbl_size *sizeof(debug_row));
    if(debug_tbl == NULL){
      printf("Mem Error debug_TBL");
      exit(-1);
    }
  }

  debug_row r = {.cc = cc, .wc = wc, .lc = lc};
  debug_tbl[id] = r;
  return 0;
}

