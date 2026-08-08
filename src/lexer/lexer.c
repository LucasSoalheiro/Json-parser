#include "lexer.h"

void free_tokens(Token_list *token_list, size_t index) {
  for (size_t i = 0; i < index; i++) {
    if (token_list->tokens[i].lexeme != NULL) {
      free(token_list->tokens[i].lexeme);
    }
  }
  free(token_list->tokens);
  free(token_list);
}

bool is_valid_number(const char *number) {
  size_t i = 0;
  if (number[i] == '-') {
    i++;
  }
  if (number[i] == '0') {
    i++;
    if (number[i] >= '0' && number[i] <= '9') {
      return false;
    }
  } else if (number[i] >= '1' && number[i] <= '9') {
    while (number[i] >= '0' && number[i] <= '9') {
      i++;
    }
  } else {
    return false;
  }
  if (number[i] == '.') {
    i++;
    if (!(number[i] >= '0' && number[i] <= '9')) {
      return false;
    }
    while (number[i] >= '0' && number[i] <= '9') {
      i++;
    }
  }
  if (number[i] == 'e' || number[i] == 'E') {
    i++;
    if (number[i] == '+' || number[i] == '-') {
      i++;
    }
    if (!(number[i] >= '0' && number[i] <= '9')) {
      return false;
    }
    while (number[i] >= '0' && number[i] <= '9') {
      i++;
    }
  }
  return number[i] == '\0';
}

char *null_token(const char *text, size_t *index) {
  if (strncmp(text + *index, "null", 4) == 0) {
    *index += 3;
    return strdup("null");
  }
  return NULL;
}

char *string_token(const char *text, size_t *index) {
  size_t end = *index + 1;
  while (text[end] != '\"') {
    if (text[end] == ',' || text[end] == '}' || text[end] == ']')
      return NULL;
    end++;
  }
  (*index)++;
  size_t string_size = (end) - *index;
  char *string = (char *)malloc(string_size + 1);
  if (string == NULL) {
    return NULL;
  }
  for (size_t i = 0; i < string_size; i++) {
    string[i] = text[*index];
    (*index)++;
  }
  string[string_size] = '\0';
  return string;
}
char *boolean_token(const char *text, size_t *index) {
  if (strncmp(text + *index, "true", 4) == 0) {
    *index += 3;
    return strdup("true");
  }
  if (strncmp(text + *index, "false", 5) == 0) {
    *index += 4;
    return strdup("false");
  }
  return NULL;
}
char *number_token(const char *text, size_t *index) {
  size_t end = *index;
  while (text[end] != ',' && text[end] != '}' && text[end] != ']') {
    end++;
  }
  size_t number_size = end - *index;

  char *number = (char *)malloc(number_size + 1);
  if (number == NULL) {
    return NULL;
  }

  for (size_t i = 0; i < number_size; i++) {
    number[i] = text[*index];
    (*index)++;
  }
  if (!is_valid_number(number)) {
    free(number);
    return NULL;
  } else {
    number[number_size] = '\0';
  }

  return number;
}

Token_list *lexer(char *text) {
  Token_list *token_list = (Token_list *)malloc(sizeof(Token_list));
  if (token_list == NULL) {
    return NULL;
  }
  token_list->count = 0;
  token_list->capacity = strlen(text);
  token_list->tokens = (Token *)malloc(token_list->capacity * sizeof(Token));
  if (!token_list->tokens) {
    free(token_list);
    return NULL;
  }
  char *lexeme_value;
  for (size_t i = 0; i < token_list->capacity; i++) {
    switch (text[i]) {
    case '{':
      token_list->tokens[token_list->count].token = TOKEN_OPEN_BRACE;
      token_list->tokens[token_list->count].lexeme = NULL;
      token_list->count++;
      break;
    case '}':
      token_list->tokens[token_list->count].token = TOKEN_CLOSE_BRACE;
      token_list->tokens[token_list->count].lexeme = NULL;
      token_list->count++;
      break;
    case '[':
      token_list->tokens[token_list->count].token = TOKEN_OPEN_BRACKET;
      token_list->tokens[token_list->count].lexeme = NULL;
      token_list->count++;
      break;
    case ']':
      token_list->tokens[token_list->count].token = TOKEN_CLOSE_BRACKET;
      token_list->tokens[token_list->count].lexeme = NULL;
      token_list->count++;
      break;
    case '\"':
      lexeme_value = string_token(text, &i);

      token_list->tokens[token_list->count].token =
          (lexeme_value != NULL) ? TOKEN_STRING : TOKEN_ERROR;
      token_list->tokens[token_list->count].lexeme = lexeme_value;
      token_list->count++;
      break;
    case ':':
      token_list->tokens[token_list->count].token =
          (lexeme_value != NULL) ? TOKEN_COLON : TOKEN_ERROR;
      token_list->tokens[token_list->count].lexeme = NULL;
      token_list->count++;
      break;
    case ',':
      token_list->tokens[token_list->count].token = TOKEN_COMMA;
      token_list->tokens[token_list->count].lexeme = NULL;
      token_list->count++;
      break;
    case 't':
    case 'f':
      lexeme_value = boolean_token(text, &i);
      token_list->tokens[token_list->count].token =
          (lexeme_value != NULL) ? TOKEN_BOOLEAN : TOKEN_ERROR;
      token_list->tokens[token_list->count].lexeme = lexeme_value;
      token_list->count++;
      break;
    case 'n':
      lexeme_value = null_token(text, &i);
      token_list->tokens[token_list->count].token =
          (lexeme_value != NULL) ? TOKEN_NULL : TOKEN_ERROR;
      token_list->tokens[token_list->count].lexeme = lexeme_value;
      token_list->count++;
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
      lexeme_value = number_token(text, &i);
      token_list->tokens[token_list->count].token = TOKEN_NUMBER;
      token_list->tokens[token_list->count].lexeme = lexeme_value;
      token_list->count++;
      break;
    case '\t':
    case '\n':
    case '\r':
    case ' ':
      break;
    }
  }
  token_list->tokens[token_list->count].token = TOKEN_EOF;
  token_list->tokens[token_list->count].lexeme = NULL;
  token_list->count++;
  return token_list;
}
