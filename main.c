#include "array.h"
#include "token.h"
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *keywords[] = {"return", "while", "for", "int", "char"};

bool check_for_keyword(const char *str) {
  for (size_t i = 0; i < sizeof(keywords) / sizeof(keywords[0]); ++i) {
    if (strcmp(str, keywords[i]) == 0)
      return true;
  }
  return false;
}

vector *tokenize(FILE *file, vector *token_array) {
  uint32_t line = 1;
  Token current;
  char c;
  while ((c = getc(file)) != EOF) {
    // either a variable or keyword
    if (is_ident_starter(c)) {
      ungetc(c, file);
      size_t i = 0;
      while (is_ident_part(c = getc(file))) {
        current.value[i++] = c;
      }
      current.value[i] = '\0';
      if (c != EOF)
        ungetc(c, file);
      current.line = line;
      if (check_for_keyword(current.value)) {
        current.type = TOKEN_KEYWORD;
        pushback(token_array, current);
      } else {
        current.type = TOKEN_IDENT;
        pushback(token_array, current);
      }
    }
    // number
    else if (isdigit(c)) {
      ungetc(c, file);
      size_t i = 0;
      while (isdigit(c = getc(file))) {
        current.value[i++] = c;
      }
      current.value[i] = '\0';
      if (c != EOF)
        ungetc(c, file);
      current.type = TOKEN_NUMBER;
      current.line = line;
      pushback(token_array, current);
    }
    // semicolon
    else if (c == ';') {
      current.value[0] = ';';
      current.value[1] = '\0';
      current.line = line;
      current.type = TOKEN_SEMICOLON;
      pushback(token_array, current);
    }
    // delimeters
    else if (is_delim(c)) {
      current.value[0] = c;
      current.value[1] = '\0';
      current.line = line;
      current.type = TOKEN_DELIM;
      pushback(token_array, current);
    }
    // newlines
    else if (c == '\n') {
      ++line;
    } else {
      current.type = TOKEN_ERROR;
      current.line = line;
      current.value[0] = c;
      current.value[1] = '\0';
    }
  }
  return token_array;
}

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
