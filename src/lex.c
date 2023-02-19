#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "lex.h"
#include "symtbl.h"

// File pointer
FILE *fp;

// Buffers
char BUF0[BUFSIZE];
char BUF1[BUFSIZE];
char **ATTRIBUTE;
int ACTIVE_F_BUF;
int ACTIVE_LB_BUF;
char *FORWARD = BUF0;
char *LEXEME_BEGIN = BUF0;

// DEBUG info
int DEBUG_TBL_ID = -1;
int CC = -1;
int LC = 1;
int WC = 0;

// Current char and it's Position
char C = '\0'; 
char NEXT = '\0'; 

// Symbol
int SYM_TBL_ID = -1;
int SYM_STATE = 0;
int SYM_LENGTH = 0;


void 
reload_buf(){
  char *buf = (ACTIVE_F_BUF)? BUF0 : BUF1;
  int read_size = fread(buf, sizeof(char), BUFSIZE-2, fp);
  buf[read_size] = EOF;
  // Swapp the buffer
  FORWARD = (ACTIVE_F_BUF)? BUF0 : BUF1;
  ACTIVE_F_BUF = ACTIVE_F_BUF ^ 1;
}


int 
advance(){
  int swapped = 0;
  if(FORWARD[0] == EOF){
    reload_buf();
    swapped = 1;
  }
  C = NEXT;
  NEXT = FORWARD[0];
  FORWARD ++;
  CC++;
  return swapped;
}

void 
sync_with_lexeme_begin(){
  FORWARD = LEXEME_BEGIN;
  ACTIVE_F_BUF = ACTIVE_LB_BUF;
}


void sync_with_forward(){
  LEXEME_BEGIN = FORWARD;
  ACTIVE_LB_BUF = ACTIVE_F_BUF ;
}


void init_lex(){
  reload_buf();
  ACTIVE_F_BUF = 0;
  ACTIVE_LB_BUF = 0;
  advance(); 
}


void advance_str_or_num(int(*f)(int)){
  int n_buf_swap = 1; 
  char *attr = calloc(BUFSIZE*n_buf_swap+1, sizeof(char));
  if(attr == NULL){
    printf("Mem Error");
    exit(-1);
  }
  int i = 0;
  attr[i] = C;
  do{
    i++;
    if(advance()){
      n_buf_swap++;
      attr = realloc(attr, BUFSIZE*n_buf_swap*sizeof(char)+1);
      if(attr == NULL){
        printf("Mem Error");
        exit(-1);
      }
    }
    attr[i] = C;
  } while((*f)(NEXT));
  attr[i+1] = '\0';
  SYM_LENGTH = i+1;
  ATTRIBUTE = &attr;
  //insert_sym_tbl(SYM_TBL_ID, attr, SYM_LENGTH);
  SYM_TBL_ID++;
}


int
get_next_token(){
  // The loop should only run while there is something to process 
  while(C != EOF ){
    // Advance FORWARD. This will update C
    sync_with_forward();
    advance(); 

    // Forward blanc space
    while(C == ' '){
      advance(); 
      sync_with_forward();
    }

    WC++;
    DEBUG_TBL_ID++;
    // Determine token
    switch (C) {
      case '\n': LC++; WC = 1; CC = 1; SYM_STATE = T_NEW_LINE; SYM_LENGTH = 1;  break;
      case ';': SYM_STATE = T_SEMICOLON; SYM_LENGTH = 1; break;
      case '(': SYM_STATE = T_LEFT_PAREN;SYM_LENGTH = 1; break;
      case ')': SYM_STATE = T_RIGHT_PAREN; SYM_LENGTH = 1; break;
      case '{': SYM_STATE = T_LEFT_BRACE; SYM_LENGTH = 1; break;
      case '}': SYM_STATE = T_RIGHT_BRACE; SYM_LENGTH = 1; break;
      case ',': SYM_STATE = T_COMMA; SYM_LENGTH = 1; break;
      case '.': SYM_STATE = T_DOT; SYM_LENGTH = 1; break;
      case '-': SYM_STATE = T_MINUS; SYM_LENGTH = 1; break;
      case '+': SYM_STATE = T_PLUS; SYM_LENGTH = 1; break;
      case '*': SYM_STATE = T_STAR; SYM_LENGTH = 1; break; 

      case '!':
                if ( NEXT == '='){
                  SYM_STATE = T_BANG_EQUAL; 
                  SYM_LENGTH = 2;
                } else {
                  SYM_STATE = T_BANG;
                  SYM_LENGTH = 1;
                }
                break;
      case '=':
                if ( NEXT == '='){
                  SYM_STATE = T_EQUAL_EQUAL; 
                  SYM_LENGTH = 2;
                } else {
                  SYM_STATE = T_EQUAL;
                  SYM_LENGTH = 1;
                }
                break;
      case EOF:
                // EOF is the sentinel character that will switch between the two different bufferss
                SYM_STATE = -1;
                break;
      default: 
                if(isalpha(C)){
                  SYM_STATE = T_ID;
                  advance_str_or_num(&isalpha);
                }else{
                  SYM_STATE = T_NUMBER;
                  advance_str_or_num(&isdigit);
                }
                break;
    }
    return SYM_STATE;
  }
  // this should not happen
  exit(-1);
}
