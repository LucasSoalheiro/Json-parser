#ifndef LEXER_H
#define LEXER_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
  TOKEN_NUMBER,
  TOKEN_BOOLEAN,
  TOKEN_STRING,
  TOKEN_NULL,

  TOKEN_OPEN_BRACKET,  // [
  TOKEN_CLOSE_BRACKET, // ]
  TOKEN_COMMA,         // ,
  TOKEN_OPEN_BRACE,    // {
  TOKEN_CLOSE_BRACE,   // }
  TOKEN_COLON,         // :
  TOKEN_EOF,
  TOKEN_ERROR,
} Token_type;

typedef struct Token {
  Token_type token;
  char *lexeme;
} Token;
typedef struct Token_list {
  size_t count;
  size_t capacity;
  Token *tokens;
} Token_list;
Token_list *lexer(char *text);
void free_tokens(Token_list *token_list);
#endif
