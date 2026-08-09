#include "parser/parser.h"
#include <stdio.h>
int main() {
  FILE *file = fopen("level3.json", "r");
  if (!file) {
    return 1;
  }

  fseek(file, 0, SEEK_END);
  long file_size = ftell(file);
  rewind(file);
  char *content = (char *)malloc(file_size + 1);
  if (content == NULL) {
    printf("Error\n");
    fclose(file);
    return 1;
  }

  size_t bytes = fread(content, 1, file_size, file);
  content[bytes] = '\0';
  parser(content);
  free(content);
  fclose(file);

  return 0;
  return 0;
}
