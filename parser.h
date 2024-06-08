#ifndef PARSER_H
#define PARSER_H

#include "array.h"
#include "ast.h"
#include <stdbool.h>

ASTNode *parse_program(vector *tokens);
ASTNode *parse_function(vector *tokens);
ASTNode *parse_statement(vector *tokens);
ASTNode *parse_expression(vector *tokens);
ASTNode *parse_declaration(vector *tokens);
ASTNode *parse_assignment(vector *tokens);
ASTNode *parse_return(vector *tokens);
bool match(vector *tokens, TokenType type, const char *value);

#endif
