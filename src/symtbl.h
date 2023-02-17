#ifndef SYMTBL_H
#define SYMTBL_H

typedef struct sym_row{
 int id;
 char *attribute;
} sym_row;

//extern sym_row **SYM_TBL;
//extern sym_row (*SYM_TBL)[];
//void
//init_sym_tbl(sym_row*);


int 
insert_sym_tbl(sym_row*, int, char*, int);

#endif

