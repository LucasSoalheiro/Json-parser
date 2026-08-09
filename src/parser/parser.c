#include "./parser.h"

void parser(char *json) {
  Token_list *token = lexer(json);
  // for (size_t i = 0; i < token->count; i++) {
  //   printf("\nToken type: %d\nLexeme: %s\n", token->tokens[i].token,
  //          token->tokens[i].lexeme);
  // }
  show_token_list(token);
  free_tokens(token);
}
