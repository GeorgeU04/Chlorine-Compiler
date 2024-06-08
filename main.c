#include "array.h"
#include "ast.h"
#include "generate.h"
#include "parser.h"
#include "tokenizer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "[ERROR]: Must provide file path as an argument\n");
    exit(EXIT_FAILURE);
  }

  FILE *file = fopen(argv[1], "r");
  if (file == NULL) {
    fprintf(stderr, "[ERROR]: File could not be opened\n");
    exit(EXIT_FAILURE);
  }

  vector *token_array;
  init_vector(&token_array, 128);
  token_array = tokenize(file, token_array);
  if (!token_array) {
    fprintf(stderr, "[ERROR]: Tokenizer failed\n");
    fclose(file);
    exit(EXIT_FAILURE);
  }
  fclose(file);

  ASTNode *ast = parse_program(token_array);
  if (!ast) {
    free(token_array->array);
    free(token_array);
    fprintf(stderr, "[ERROR]: Parser failed\n");
    exit(EXIT_FAILURE);
  }

  // print_ast(ast, 0);

  open_output("output.asm");
  generate_statements(ast);
  free(token_array->array);
  free(token_array);
  free_ast(ast);
  close_output();
  return 0;
}
