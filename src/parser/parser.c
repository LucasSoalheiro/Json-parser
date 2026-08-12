#include "./parser.h"

void parser(char *path, bool analitic) {
  Token_list *token = lexer(path);
  // for (size_t i = 0; i < token->count; i++) {
  //   printf("\nToken type: %d\nLexeme: %s\n", token->tokens[i].token,
  //          token->tokens[i].lexeme);
  // }
  if (analitic)
    show_token_list(token);
  free_tokens(token);
}
