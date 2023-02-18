#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helper.h"
#include "lex.h"
#include "token.h"
#include "parser.h"
#include "vm.h"

Expr *parse(Expr *expr, Token *t){
  Expr *e = malloc(sizeof(Expr*));
  if(e == NULL){
    printf("Memory Error at parse function\n");
  }

  e->token = t;
  e->left = expr;
  e->right = NULL;
  return e;
}

/*
Token **pt = NULL;
int ip = 0;
__int8_t code[CODESIZE] = {'\0'};     // Code memory

const char* getExprTypeName(int type){
   switch (type)
   {
     case LITERAL: return "LITERAL";
     case UNARY: return "UNARY";
     case BINARY: return "BINARY";
     case GROUPING: return "GROUPING";
     default: return "";
   }
}

void treePrintTree(Expr *root, int level){
  if (root == NULL){
    return;
  }
  for (int i = 0; i < level; i++)
    printf(i == level - 1 ? "| " : "    ");
  printf("%s\n", root->operator->lexeme);
  treePrintTree(root->left, level + 1);
  treePrintTree(root->right, level + 1);
}
void treePrintInfo(Expr *root, int level){
  if (root == NULL){
    return;
  }
  printf("Level: %5d%10s%5s\n",level, getExprTypeName(root->type), root->operator->lexeme);
  treePrintInfo(root->left, level + 1);
  treePrintInfo(root->right, level + 1);
}

void treePrint(Expr *root, int level)
{
  treePrintTree(root, 1);
  treePrintInfo(root, 1);
}

void treeWalk(Expr *e) {
  if(e == NULL){
    return;
  }

  switch (e->type){
     case LITERAL: 
       if(e->operator->name == T_NUMBER){
         code[ip++] = ICONST;
         code[ip++] = atoi(e->operator->lexeme);
         printf("ICONST, %s,\n", e->operator->lexeme);
       }
       return;
     default:
       printf("Error:  Unsupported %s type %s\n", getExprTypeName(e->type), getOperatorNameName(e->operator->name));
     case BINARY: 
       switch(e->operator->name){
         case T_PLUS:
           treeWalk(e->left);
           treeWalk(e->right);
           code[ip++] = IADD;
           printf("IADD,\n");
           return;
         case T_STAR:
           treeWalk(e->left);
           treeWalk(e->right);
           code[ip++] = IMUL;
           printf("IMUL,\n");
           return;
         case T_MINUS:
           treeWalk(e->right);
           treeWalk(e->left);
           code[ip++] = ISUB;
           printf("ISUB,\n");
           return;
         default:
           printf("Error:  Unsupported %s type %s\n", getExprTypeName(e->type), getOperatorNameName(e->operator->name));
       }
     case UNARY: 
       switch(e->operator->name){
         case T_MINUS:
           //treeWalk(e->left); 
           treeWalk(e->right); 
           code[ip-1] = code[ip-1]/-1;
           //code[ip++] = IADD;
           printf("Make negative,\n");
           //printf("IADD,\n");
           return;
       }
       return;
     case GROUPING: 
       treeWalk(e->left); 
       return;
  }

}

void generateCode(Expr *e){
  treePrint(e, 1);


  treeWalk(e);
  code[ip++] = PRINT;
  code[ip++] = HALT;

  FILE *write_ptr;
  write_ptr = fopen("./test/program.bin","wb");  // w for write, b for binary
  fwrite(code,sizeof(code),1,write_ptr); // write from our buffer
  fclose(write_ptr);

  for(int i = 0; i < CODESIZE; i++){
    printf("%d", code[i]);
  }
 }

Expr *newExpr(Expr *left, enum ExprType type, Token *operator, Expr *right)                                                                             {
  Expr *e = malloc(sizeof(Expr));

  if(e == NULL){
    die("Memory Error!");
  }

  e->left = left;
  e->type = type;
  e->operator = operator;
  e->right = right;

  return e;
}


void printExpr(Expr *e){
  printf("left: %p\n", &(e->left));
  printf("operator: %s\n", getOperatorNameName(e->operator->name));
  printf("right: %p\n", &(e->right));
}

void synchronize() {
  pt=&(*pt)->next;
    while((*pt) != NULL) {
      if((*pt)->prev->name == T_SEMICOLON) return;

      switch ((*pt)->next->name) {
        case T_CLASS:
        case T_FUN:
        case T_VAR:
        case T_FOR:
        case T_IF:
        case T_WHILE:
        case T_PRINT:
        case T_RETURN:
          return;
      }
      pt=&(*pt)->next;
    }
}

int notAtEnd(){ 
  return (*pt) != NULL;
}

int match(enum TokenValue name){
  return name == (*pt)->name; 
}

void advance(){
    if(notAtEnd()){
      pt=&(*pt)->next;
    }else{
      printf("Error: Unexpected EOF at line: %d word: %d near %s \n", (*pt)->line, (*pt)->word,(*pt)->prev->lexeme);
    }
}

Token *consume(){
    Token *o = (*pt);
    advance();
    return o;
}

struct Expr *primary(){
  if(notAtEnd() && (match(T_STRING) || match(T_NUMBER))){
    return newExpr(NULL, LITERAL, consume(), NULL);
  }
  if(notAtEnd() && match(T_LEFT_PAREN)){
    Token *o = consume();
    Expr *e = expression(pt);
    if(notAtEnd() && !(match(T_RIGHT_PAREN))){
      printf("Error: Expecting ) at line: %d word: %d near %s \n", (*pt)->line, (*pt)->word,(*pt)->prev->lexeme);
    }
    advance();
    return newExpr(e, GROUPING, o, NULL);
  }
  printf("Error: Syntax error at line: %d word: %d near %s \n", (*pt)->line, (*pt)->word,(*pt)->prev->lexeme);
  return newExpr(NULL, '\0', NULL, NULL);
}


struct Expr *unary(){
  if(notAtEnd() && (match(T_BANG) || match(T_MINUS))){
    Token *o = consume();
    Expr *right = unary(); 
    Expr *this = newExpr(NULL, UNARY, o, right);
    return this;
  }
  return primary();
}


struct Expr *factor(){
  Expr *left = unary(); 
  while (notAtEnd() && (match(T_SLASH) || match(T_STAR))){
    Token *o = consume();
    Expr *right = unary(); 
    left = newExpr(left, BINARY, o, right);
  }
    return left;
}


struct Expr *term(){
  Expr *left = factor(); 
  while (notAtEnd() && (match(T_MINUS) || (match(T_PLUS)))){
    Token *o = consume(); 
    Expr *right = factor(); 
    left = newExpr(left, BINARY, o, right);
  }
  return left;
}

struct Expr *comparison(){
  Expr *left = term();
  while (notAtEnd() && (match(T_GREATER) || match(T_GREATER_EQUAL) || (match(T_LESS) || match(T_LESS_EQUAL)))){
    Token *o = consume(); 
    Expr *right = term(); 
    left = newExpr(left, BINARY, o, right);
  }
  return left;
}

struct Expr *equality(){
  Expr *left = comparison(); 
  while (notAtEnd() && (match(T_BANG_EQUAL) || match(T_EQUAL_EQUAL))){
    Token *o = consume(); 
    Expr *right = comparison(); 
    left = newExpr(left, BINARY,  o, right);
  }
  return left;
}


Expr *expression(Token **t){
  pt = t;
  Expr *e = equality();
  return e;
}
*/
