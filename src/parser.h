#ifndef PARSER_H
#define PARSER_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
  JSON_INT,           // integer numbers: 	1
  JSON_DECIMAL,       // decimal numbers: 	1.23
  JSON_BOOLEAN,       // boolean: 		true | false
  JSON_STRING,        // string: 		"text"
  JSON_ARRAY,         // array: 		[]
  JSON_OBJECT,        // object: 		{}
  JSON_QUOTES,        // quote: 		""
  JSON_OPEN_BRACKET,  // open bracket: 		[
  JSON_CLOSE_BRACKET, // close bracket: 	]
  JSON_COMMA,         // comma: 		,
  JSON_OPEN_BRACE,    // open brace: 		{
  JSON_CLOSE_BRACE,   // close brace: 		}
  JSON_COLON,         // colon:			:
} JSON_TYPES;

typedef struct JSON {
  char *key;
  JSON_TYPES data_type;
  union {
    double number;
    bool boolean;
    char *string;
    struct JSON *object;
  } value;
  JSON *next;
} JSON;

void parser();
#endif
