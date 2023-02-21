#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helper.h"
#include "token.h"

Token *newToken(int name, sym_row* symbol){
  Token *t = malloc(sizeof(Token));
  if(t == NULL){
    printf("Memory Error newToken\n");
    exit(-1);
  }
  t->name = name;
  t->symbol = symbol;
  return t;
}


const char* get_token_name(int token)
{
   switch (token)
   {
     // One or two character tokens.
     case T_ID: return "T_ID";
     case T_NUMBER: return "T_NUMBER";

     // Keywords.
     case T_NEW_LINE: return "T_NEW_LINE";
     case T_SEMICOLON: return "T_SEMICOLON";
     case T_CLASS: return "T_CLASS";
     case T_ELSE: return "T_ELSE";
     case T_FALSE: return "T_FALSE";
     case T_FUN: return "T_FUN";
     case T_FOR: return "T_FOR";
     case T_IF: return "T_IF";
     case T_NIL: return "T_NIL";
     case T_PRINT: return "T_PRINT";
     case T_RETURN: return "T_RETURN";
     case T_SUPER: return "T_SUPER";
     case T_THIS: return "T_THIS";
     case T_TRUE: return "T_TRUE";
     case T_VAR: return "T_VAR";
     case T_WHILE: return "T_WHILE";
     case T_LEFT_PAREN: return "T_LEFT_PAREN";
     case T_RIGHT_PAREN: return "T_RIGHT_PAREN";
     case T_LEFT_BRACE: return "T_LEFT_BRACE";
     case T_RIGHT_BRACE: return "T_RIGHT_BRACE";
     case T_COMMA: return "T_COMMA";
     case T_DOT: return "T_DOT";
     case T_MINUS: return "T_MINUS";
     case T_PLUS: return "T_PLUS";
     case T_SLASH: return "T_SLASH";
     case T_STAR: return "T_STAR";
     case T_BANG: return "T_BANG";
     case T_BANG_EQUAL: return "T_BANG_EQUAL";
     case T_EQUAL: return "T_EQUAL";
     case T_EQUAL_EQUAL: return "T_EQUAL_EQUAL";
     case T_GREATER: return "T_GREATER";
     case T_GREATER_EQUAL: return "T_GREATER_EQUAL";
     case T_LESS: return "T_LESS";
     case T_LESS_EQUAL: return "T_LESS_EQUAL";
     case T_OR: return "T_OR";
     case T_AND: return "T_AND";
     default: return "";
   }
}

/*
Token *addToken(Token *head, int name, int lex_length, char *lex, int sym_id, int character, int word, int line){
	Token *t = malloc(sizeof(Token));
	if(t == NULL){
		die("Memory Error!");
	}

	//t->attribute = malloc(sizeof(T_attribute));
	if(t == NULL){
		die("Memory Error!");
	}

	if(head != NULL){
		head->next = t;
	}
	t->name = name;
  t->debug_row = newDebugRow(line, character, word);
  if(name == T_ID || name == T_NUMBER){
    t->attribute = malloc(sizeof(sizeof(char)*lex_length+1));
    if(t->attribute == NULL){
      printf("Mem Error creating attribute");
      exit(-1);
    }
    for(int i=0; i< lex_length; i++) {
      t->attribute[i] = lex[i];
    }
    t->attribute[lex_length] = '\0';
  } else {
    t->attribute = NULL;
  }
  t->prev = head;
	t->next = NULL;
	return t;
}

Token *rewindTokenList(Token *t){
  if (t == NULL){
    printf("Token list is empty.\n");
    exit(-1);
  }
  while(t->prev != NULL){
    t = t->prev;
  }
  return t;
}


void destroyToken(Token *t){
  if(t != NULL){
    if(t->lexeme != NULL){
      free(t->lexeme);
    }
    free(t);
  }
}


void destroyTokens(Token *t){
	t = rewindTokenList(t);
	if(t == NULL) {
		return;
	}
  while(t->next!= NULL){
		t = t->next;
		destroyToken(t->prev);
  }
	destroyToken(t);
}

const char *getTokenAttribute(Token *t){
  if(t->attribute == NULL ) {
    return "";
  } else {
    return t->attribute;
  }
}

void printTokens(Token *t){
	t = rewindTokenList(t);
  while(t != NULL){
       printf("ln: %-3d cc: %-3d word: %-3d name: %-12s attribute : %-15s\n",t->debug_row->line, t->debug_row->character, t->debug_row->word,getOperatorNameName(t->name),getTokenAttribute(t));
    t = t->next;
  }
  return;
}
*/
