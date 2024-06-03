#include "array.h"
#include "tokenizer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "[ERROR]: Must provide file path as an argument");
    exit(EXIT_FAILURE);
  }

  FILE *file;
  file = fopen(argv[1], "r");
  if (file == NULL) {
    fprintf(stderr, "[ERORR]: File could not be opened");
    exit(EXIT_FAILURE);
  }

  vector *token_array;
  init_vector(&token_array, 128);
  token_array = tokenize(file, token_array);
  print_vector(token_array);

  free(token_array->array);
  free(token_array);
  fclose(file);
  return 0;
}
