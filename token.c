#include <ctype.h>
#include <stdbool.h>
#include <string.h>

bool is_ident_starter(char c) { return (isalpha(c)) || (c == '_'); }
bool is_ident_part(char c) { return (isalnum(c)) || (c == '_'); }
bool is_space(char c) { return c == ' '; }
bool is_delim(char c) {
  return c == ')' || c == '(' || c == '{' || c == '}' || c == '[' || c == '[';
}
bool is_operator(char c) { return strchr("+-*/%&|^~!=<>", c) != NULL; }
