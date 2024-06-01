#ifndef TOKEN_H
#define TOKEN_H
#include <stdbool.h>
#include <stdint.h>

typedef enum {
  TOKEN_NUMBER,
  TOKEN_IDENT,
  TOKEN_KEYWORD,
  TOKEN_OPERATOR,
  TOKEN_COMMENT,
  TOKEN_DELIM,
  TOKEN_SEMICOLON,
  TOKEN_ERROR
} TokenType;

typedef struct {
  TokenType type;
  char value[32];
  uint32_t line;
} Token;

bool is_ident_starter(char c);
bool is_ident_part(char c);
bool is_space(char c);
bool is_delim(char c);
#endif
