#ifndef PARSER_H
#define PARSER_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
  JSON_INT,
  JSON_DECIMAL,
  JSON_TRUE,
  JSON_FALSE,
  JSON_STRING,
  JSON_NULL,
  JSON_ARRAY,
  JSON_OBJECT,

  JSON_QUOTES,        // ""
  JSON_OPEN_BRACKET,  // [
  JSON_CLOSE_BRACKET, // ]
  JSON_COMMA,         // ,
  JSON_OPEN_BRACE,    // {
  JSON_CLOSE_BRACE,   // }
  JSON_COLON,         // :
  JSON_EOF,
} JSON_TYPES;

typedef struct JSON {
  char *key;
  JSON_TYPES data_type;
} JSON;

void parser();
#endif
