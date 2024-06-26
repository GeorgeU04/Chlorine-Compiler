#include "array.h"
#include "token.h"
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
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
    }
    // comments
    else if (c == '/' && (c = getc(file)) == '/') {
      while (((c = getc(file)) != '\n') && c != EOF) {
      }
      current.type = TOKEN_COMMENT;
      current.line = line;
      current.value[0] = '/';
      current.value[1] = '/';
      current.value[2] = '\0';
      pushback(token_array, current);
      if (c == '\n') {
        ++line;
      }
    }
    // operators
    else if (is_operator(c)) {
      ungetc(c, file);
      size_t i = 0;
      while (is_operator((c = getc(file)))) {
        current.value[i++] = c;
      }
      current.value[i] = '\0';
      if (c != EOF)
        ungetc(c, file);
      current.type = TOKEN_OPERATOR;
      current.line = line;
      pushback(token_array, current);
    }
    // spaces
    else if (is_space(c)) {
      continue;
    } else {
      current.type = TOKEN_ERROR;
      current.line = line;
      current.value[0] = c;
      current.value[1] = '\0';
      pushback(token_array, current);
    }
  }
  return token_array;
}
