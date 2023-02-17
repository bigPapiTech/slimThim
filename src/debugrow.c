#include <stdlib.h>
#include <stdio.h>
#include "debugrow.h"


DebugRow *newDebugRow(int line, int character, int word){
  DebugRow *r = malloc(sizeof(DebugRow));
  if(r == NULL){
    printf("Mem Error creating DebugRow");
    exit(-1);
  }
  r->line = line;
  r->character = character;
  r->word = word;
  return r;
}

