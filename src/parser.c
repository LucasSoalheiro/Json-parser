#include "parser.h"

bool is_number(char number) {
  char numbers[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '-', '.'};
  for (size_t i = 0; i < 12; i++) {
    if (number == numbers[i])
      return true;
  }
  return false;
}

char *null_token(char *json, size_t *index) {
  if (strncmp(json + *index, "null", 4) == 0) {
    *index += 3;
    return strdup("null");
  }
  return NULL;
}

char *string_token(char *json, size_t *index) {
  size_t end = *index + 1;
  while (json[end] != '\"') {
    end++;
  }
  (*index)++;
  size_t string_size = (end) - *index;
  char *string = (char *)malloc(string_size + 1);
  if (string == NULL) {
    return NULL;
  }
  for (size_t i = 0; i < string_size; i++) {
    string[i] = json[*index];
    (*index)++;
  }
  string[string_size] = '\0';
  return string;
}
char *boolean_token(char *json, size_t *index) {
  if (strncmp(json + *index, "true", 4) == 0) {
    *index += 3;
    return strdup("true");
  }
  if (strncmp(json + *index, "false", 5) == 0) {
    *index += 4;
    return strdup("false");
  }
  return NULL;
}
char *number_token(char *json, size_t *index) {
  size_t end = *index;
  while (json[end] != ',' && json[end] != '}' && json[end] != ']') {
    end++;
  }
  size_t number_size = end - *index;

  char *number = (char *)malloc(number_size + 1);
  if (number == NULL) {
    return NULL;
  }

  for (size_t i = 0; i < number_size; i++) {
    number[i] = json[*index];
    if (!is_number(json[*index])) {
      free(number);
      return NULL;
    }
    (*index)++;
  }
  number[number_size] = '\0';
  return number;
}

void lexer() {
  char json[] =
      "{\"name\":\"Lucas\",\"age\":-19.90,\"isStudent\":true,\"money\":null}";
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
    case 'f':
      token = boolean_token(json, &i);
      printf("BOOLEAN(%s) ", token);
      free(token);
      break;
    case 'n':
      token = null_token(json, &i);
      if (strcmp(token, "null") == 0) {
        printf("NULL ");
      }
      free(token);
      break;
    case '\0':
      printf("EOF ");
      break;
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    case '-':
      token = number_token(json, &i);
      printf("NUMBER(%s) ", token);
      free(token);
      break;
    }
  }
  free(json_lexer);
}

void parser() { lexer(); }
