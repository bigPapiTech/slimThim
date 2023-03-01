#ifndef DEBUGTBL_H
#define DEBUGTBL_H

typedef struct debug_row{
 int cc;
 int wc;
 int lc;
} debug_row;


int
insert_debug_tbl(debug_row*, int, int, int, int);

#endif

