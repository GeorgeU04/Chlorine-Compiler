#include "parser.h"
#include "array.h"
#include "token.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int32_t token_index = 0;

bool match(vector *tokens, TokenType type, const char *value) {
  if (token_index >= tokens->size) {
    printf("Index out of range silly goose\n");
    return false;
  }

  Token *current_token = get_item(tokens, token_index);
  if (current_token->type == type &&
      (!value || strcmp(current_token->value, value) == 0)) {
    // printf("Matched: %s\n", current_token->value);
    ++token_index;
    return true;
  }
  return false;
}

ASTNode *parse_program(vector *tokens) {
  ASTNode *functions = NULL;
  ASTNode **current = &functions;
  while (token_index < tokens->size) {
    ASTNode *function = parse_function(tokens);
    if (!function) {
      break;
    }
    *current = function;
    current = &function->next;
  }
  return create_program_node(functions);
}

ASTNode *parse_function(vector *tokens) {
  if (match(tokens, TOKEN_KEYWORD, "int")) {
    Token *token = get_item(tokens, token_index);
    if (!token)
      return NULL;
    if (match(tokens, TOKEN_IDENT, NULL)) {
      char *name = strdup(token->value);
      if (match(tokens, TOKEN_DELIM, "(") && match(tokens, TOKEN_DELIM, ")") &&
          match(tokens, TOKEN_DELIM, "{")) {
        ASTNode *stmts = NULL;
        ASTNode **current = &stmts;
        while (!match(tokens, TOKEN_DELIM, "}")) {
          ASTNode *stmt = parse_statement(tokens);
          if (!stmt)
            break;
          *current = stmt;
          current = &stmt->next;
        }
        return create_function_node(stmts, name);
      }
      free(name);
    }
  }
  return NULL;
}

ASTNode *parse_statement(vector *tokens) {
  if (token_index >= tokens->size)
    return NULL;
  Token *token = get_item(tokens, token_index);
  if (!token)
    return NULL;
  if (token->type == TOKEN_KEYWORD && strcmp(token->value, "int") == 0) {
    return parse_declaration(tokens);
  } else if (token->type == TOKEN_IDENT) {
    return parse_assignment(tokens);
  } else if (token->type == TOKEN_KEYWORD &&
             strcmp(token->value, "return") == 0) {
    return parse_return(tokens);
  } else if (token->type == TOKEN_DELIM && strcmp(token->value, "{") == 0) {
    match(tokens, TOKEN_DELIM, "{");
    ASTNode *stmts = NULL;
    ASTNode **current = &stmts;
    while (token_index < tokens->size) {
      token = get_item(tokens, token_index);
      if (token->type == TOKEN_DELIM && strcmp(token->value, "}") == 0) {
        match(tokens, TOKEN_DELIM, "}");
        break;
      }
      ASTNode *stmt = parse_statement(tokens);
      if (!stmt)
        return NULL;
      *current = stmt;
      current = &stmt->next;
    }
    return create_compound_stmt_node(stmts);
  } else if (token->type == TOKEN_SEMICOLON) {
    match(tokens, TOKEN_SEMICOLON, ";");
    return NULL;
  }
  return NULL;
}

ASTNode *parse_declaration(vector *tokens) {
  match(tokens, TOKEN_KEYWORD, "int");
  Token *token = get_item(tokens, token_index);
  if (match(tokens, TOKEN_IDENT, NULL)) {
    char *var_name = strdup(token->value);
    ASTNode *init_value = NULL;
    if (match(tokens, TOKEN_OPERATOR, "=")) {
      init_value = parse_expression(tokens);
    }
    if (match(tokens, TOKEN_SEMICOLON, ";")) {
      return create_declaration_node(init_value, var_name);
    }
    free(var_name);
  }
  return NULL;
}

ASTNode *parse_assignment(vector *tokens) {
  Token *token = get_item(tokens, token_index);
  if (match(tokens, TOKEN_IDENT, NULL)) {
    char *var_name = strdup(token->value);
    if (match(tokens, TOKEN_OPERATOR, "=")) {
      ASTNode *value = parse_expression(tokens);
      if (match(tokens, TOKEN_SEMICOLON, ";")) {
        return create_assignment_node(value, var_name);
      }
    }
    free(var_name);
  }
  return NULL;
}

ASTNode *parse_return(vector *tokens) {
  match(tokens, TOKEN_KEYWORD, "return");
  ASTNode *value = parse_expression(tokens);
  if (match(tokens, TOKEN_SEMICOLON, ";")) {
    return create_return_node(value);
  }
  return NULL;
}

ASTNode *parse_expression(vector *tokens) {
  Token *token = get_item(tokens, token_index);
  if (!token)
    return NULL;
  if (token->type == TOKEN_NUMBER) {
    match(tokens, TOKEN_NUMBER, NULL);
    return create_literal_node(atoi(token->value));
  } else if (token->type == TOKEN_IDENT) {
    match(tokens, TOKEN_IDENT, NULL);
    return create_identifier_node(strdup(token->value));
  } else if (match(tokens, TOKEN_DELIM, "(")) {
    ASTNode *expr = parse_expression(tokens);
    match(tokens, TOKEN_DELIM, ")");
    return expr;
  } else {
    ASTNode *left = parse_expression(tokens);
    token = get_item(tokens, token_index);
    if (token && token->type == TOKEN_OPERATOR) {
      char op = token->value[0];
      ++token_index;
      ASTNode *right = parse_expression(tokens);
      return create_binary_op_node(left, right, op);
    }
    return left;
  }
}
