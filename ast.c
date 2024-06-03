#include "ast.h"
#include <stdlib.h>

ASTNode *create_program_node(ASTNode *functions) {
  ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
  node->type = AST_PROGRAM;
  node->data.program.functions = functions;
  node->next = NULL;
  return node;
}
ASTNode *create_function_node(ASTNode *body, char *name) {
  ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
  node->type = AST_FUNCTION;
  node->data.function.body = body;
  node->data.function.name = name;
  node->next = NULL;
  return node;
}
ASTNode *create_compound_stmt_node(ASTNode *stmts) {
  ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
  node->type = AST_COMPOUND_STMT;
  node->data.compound_stmt.stmts = stmts;
  node->next = NULL;
  return node;
}
ASTNode *create_declaration_node(ASTNode *init_value, char *var_name) {
  ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
  node->type = AST_DECLARATION;
  node->data.declaration.init_value = init_value;
  node->data.declaration.var_name = var_name;
  node->next = NULL;
  return node;
}
ASTNode *create_assignmnet_node(ASTNode *value, char *var_name) {
  ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
  node->type = AST_ASSIGNMENT;
  node->data.assignment.value = value;
  node->data.assignment.var_name = var_name;
  node->next = NULL;
  return node;
}
ASTNode *create_return_node(ASTNode *value) {
  ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
  node->type = AST_RETURN;
  node->data.return_stmt.value = value;
  node->next = NULL;
  return node;
}
ASTNode *create_binary_op_node(ASTNode *left, ASTNode *right, char op) {
  ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
  node->type = AST_BINARY_OP;
  node->data.binary_op.left = left;
  node->data.binary_op.right = right;
  node->data.binary_op.op = op;
  node->next = NULL;
  return node;
}
ASTNode *create_literal_node(int value) {
  ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
  node->type = AST_LITERAL;
  node->data.literal.value = value;
  node->next = NULL;
  return node;
}
ASTNode *create_identifier_node(char *name) {
  ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
  node->type = AST_IDENTIFIER;
  node->data.identifier.name = name;
  node->next = NULL;
  return node;
}
