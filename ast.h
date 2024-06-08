#ifndef AST_H
#define AST_H

#include <stdint.h>
#include <stdlib.h>
typedef enum {
  AST_PROGRAM,
  AST_FUNCTION,
  AST_COMPOUND_STMT,
  AST_DECLARATION,
  AST_ASSIGNMENT,
  AST_RETURN,
  AST_BINARY_OP,
  AST_LITERAL,
  AST_IDENTIFIER
} ASTNodeType;

typedef struct ASTNode {
  ASTNodeType type;
  struct ASTNode *next;
  union {
    // Program node
    struct {
      struct ASTNode *functions;
    } program;

    // Function node
    struct {
      char *name;
      struct ASTNode *body;
    } function;

    // Compound statement node
    struct {
      struct ASTNode *stmts;
    } compound_stmt;

    // Declaration node
    struct {
      char *var_name;
      struct ASTNode *init_value;
    } declaration;

    // Assignment node
    struct {
      char *var_name;
      struct ASTNode *value;
    } assignment;

    // Return node
    struct {
      struct ASTNode *value;
    } return_stmt;

    // Binary operation node
    struct {
      struct ASTNode *left;
      char op;
      struct ASTNode *right;
    } binary_op;

    // Literal node
    struct {
      int value;
    } literal;

    // Identifier node
    struct {
      char *name;
    } identifier;
  } data;
} ASTNode;

ASTNode *create_program_node(ASTNode *functions);
ASTNode *create_function_node(ASTNode *body, char *name);
ASTNode *create_compound_stmt_node(ASTNode *stmts);
ASTNode *create_declaration_node(ASTNode *init_value, char *var_name);
ASTNode *create_assignment_node(ASTNode *value, char *var_name);
ASTNode *create_return_node(ASTNode *value);
ASTNode *create_binary_op_node(ASTNode *left, ASTNode *right, char op);
ASTNode *create_literal_node(int value);
ASTNode *create_identifier_node(char *name);
void free_ast(ASTNode *node);
void print_ast(ASTNode *node, int32_t space);
#endif
