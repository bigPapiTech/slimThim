#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lex.h"
#include "parser.h"
#include "helper.h"


void die(char *msg){
  printf("%s\n", msg);
  exit(1);
}

void checkInput(int argc){
  if(argc < 2){
    die("Provide a filename");
  }
}


char *mallocChar(int size){
  char *ptr = malloc(size);
  if(ptr == NULL){
    die("Memory Error!");
  }
  return ptr;
}

char *copyStr(char *src){
  int size = (char)strlen(src) + 1;
  char *dst = mallocChar(size);
  strlcpy(dst, src, size);
  return dst;
}

char *copyFpToMem(FILE* fp, int size){
  char *mem = mallocChar(size + 1);// \0
	int c;
	int i = 0;
	while((c = fgetc(fp)) != EOF){
		mem[i] = c;
		i++;
	}
	mem[size] = '\0';
	return mem;
}

FILE* openFile(char *filePath, char *mode){
  FILE *fp = fopen(filePath, mode );
  if (fp == NULL){
    die("Could not read source file");
  }
  return fp; 
}

int getFileSize(FILE *fp){
  fseek(fp, 0L, SEEK_END);
  int sz = ftell(fp);
  rewind(fp);
  return sz;
}

/*

const char* getOperatorTypeName(enum TokenType type)
{
   switch (type)
   {
     case LEFT_PAREN: return "LEFT_PAREN";
     case RIGHT_PAREN: return "RIGHT_PAREN";
     case LEFT_BRACE: return "LEFT_BRACE";
     case RIGHT_BRACE: return "RIGHT_BRACE";
     case COMMA: return "COMMA";
     case DOT: return "DOT";
     case MINUS: return "MINUS";
     case PLUS: return "PLUS";
     case SEMICOLON: return "SEMICOLON";
     case SLASH: return "SLASH";
     case STAR: return "STAR";

  // One or two character tokens.
     case BANG: return "BANG";
     case BANG_EQUAL: return "BANG_EQUAL";
     case EQUAL: return "EQUAL";
     case EQUAL_EQUAL: return "EQUAL_EQUAL";
     case GREATER: return "GREATER";
     case GREATER_EQUAL: return "GREATER_EQUAL";
     case LESS: return "LESS";
     case LESS_EQUAL: return "LESS_EQUAL";

  // Literals.
     case IDENTIFIER: return "IDENTIFIER";
     case STRING: return "STRING";
     case NUMBER: return "NUMBER";

  // Keywords.
     case AND: return "AND";
     case CLASS: return "CLASS";
     case ELSE: return "ELSE";
     case FALSE: return "FALSE";
     case FUN: return "FUN";
     case FOR: return "FOR";
     case IF: return "IF";
     case NIL: return "NIL";
     case OR: return "OR";
     case PRINT: return "PRINT";
     case RETURN: return "RETURN";
     case SUPER: return "SUPER";
     case THIS: return "THIS";
     case TRUE: return "TRUE";
     case VAR: return "VAR";
     case WHILE: return "WHILE";
   };
}
*/
/*
const char* getExprTypeName(enum ExprType type){
   switch (type)
   {
     case LITERAL: return "LITERAL";
     case UNARY: return "UNARY";
     case BINARY: return "BINARY";
     case GROUPING: return "GROUPING";
   }
};


void treePrint(Expr *root, int level)
{
  if (root == NULL)
    return;
  for (int i = 0; i < level; i++)
    printf(i == level - 1 ? "| " : "    ");
  printf("%s\n", root->operator->literal);
  treePrint(root->left, level + 1);
  treePrint(root->right, level + 1);
}
*/
