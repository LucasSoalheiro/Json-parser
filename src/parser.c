#include "parser.h"
#include <stdio.h>
#include <string.h>

char *string_token(char *json, size_t *index) {
  size_t end = *index + 1;
  while (json[end] != '\"') {
    end++;
  }
  (*index)++;
  size_t string_size = (end) - *index;
  char *string = (char *)malloc(string_size + 1);
  for (size_t i = 0; i < string_size; i++) {
    string[i] = json[*index];
    (*index)++;
  }
  return string;
}
char *boolean_token(char *json, size_t *index) {
  size_t end = *index;
  while (json[end] != ',' && json[end] != '}') {
    end++;
  }
  size_t boolean_size = end - *index;
  char *boolean = (char *)malloc(boolean_size + 1);
  for (size_t i = 0; i < boolean_size; i++) {
    boolean[i] = json[*index];
    (*index)++;
  }
  return boolean;
}
char *number_token(char *json, size_t *index) {
  size_t end = *index;
  while (json[end] != ',' && json[end] != '}') {
    end++;
  }
  size_t number_size = end - *index;
  char *number = (char *)malloc(number_size + 1);
  for (size_t i = 0; i < number_size; i++) {
    number[i] = json[*index];
    (*index)++;
  }
  return number;
}

void lexer() {
  char json[] = "{\"name\":\"Lucas\",\"age\":19,\"isStudent\":true}\0";
  JSON *json_lexer = (JSON *)malloc(strlen(json) * sizeof(JSON));
  char *token;
  for (size_t i = 0; i < strlen(json); i++) {
    switch (json[i]) {
    case '{':
      printf("OPEN_BRACE ");
      break;
    case '}':
      printf("CLOSE_BRACE ");
      break;
    case '[':
      printf("OPEN_BRACKET ");
      break;
    case ']':
      printf("CLOSE_BRACKET ");
      break;
    case '\"':
      token = string_token(json, &i);
      printf("STRING(%s) ", token);
      free(token);
      break;
    case ':':
      printf("COLON ");
      break;
    case ',':
      printf("COMMA ");
      break;
    case 't':
      token = boolean_token(json, &i);
      printf("BOOLEAN(%s) ", token);
      free(token);
      break;
    case 'f':
      token = boolean_token(json, &i);
      printf("BOOLEAN(%s) ", token);
      free(token);
      break;
    case 'n':
      break;
    case '\0':
      printf("EOF ");
      break;
    default:
      token = number_token(json, &i);
      printf("NUMBER(%s) ", token);
      free(token);
      break;
    }
  }
  free(json_lexer);
}

void parser() { lexer(); }
