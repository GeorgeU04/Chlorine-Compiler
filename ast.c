#include "ast.h"
#include <stdio.h>
#include <stdlib.h>

void print_ast(ASTNode *node, int32_t space) {
  if (!node) {
    return;
  }

  for (size_t i = 0; i < space; ++i) {
    printf(" ");
  }
  switch (node->type) {
  case AST_PROGRAM:
    printf("Program\n");
    print_ast(node->data.program.functions, space + 1);
    break;
  case AST_FUNCTION:
    printf("Function: %s\n", node->data.function.name);
    print_ast(node->data.function.body, space + 1);
    break;
  case AST_DECLARATION:
    printf("Declaration: %s\n", node->data.declaration.var_name);
    print_ast(node->data.declaration.init_value, space + 1);
    break;
  case AST_ASSIGNMENT:
    printf("Assignment: %s\n", node->data.assignment.var_name);
    print_ast(node->data.assignment.value, space + 1);
    break;
  case AST_RETURN:
    printf("Return\n");
    print_ast(node->data.return_stmt.value, space + 1);
    break;
  case AST_BINARY_OP:
    printf("Binary Operation: %c\n", node->data.binary_op.op);
    print_ast(node->data.binary_op.left, space + 1);
    print_ast(node->data.binary_op.right, space + 1);
    break;
  case AST_LITERAL:
    printf("Literal: %d\n", node->data.literal.value);
    break;
  case AST_IDENTIFIER:
    printf("Identifier: %s\n", node->data.identifier.name);
    break;
  case AST_COMPOUND_STMT:
    printf("Compound Statement\n");
    print_ast(node->data.compound_stmt.stmts, space + 1);
    break;
  default:
    printf("Unknown AST Node Type\n");
    break;
  }
  print_ast(node->next, space);
}

ASTNode *create_program_node(ASTNode *functions) {
  ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
  if (!node) {
    fprintf(stderr, "Failed to allocate memory for program node\n");
    exit(EXIT_FAILURE);
  }
  node->type = AST_PROGRAM;
  node->data.program.functions = functions;
  node->next = NULL;
  return node;
}

// Create function node
ASTNode *create_function_node(ASTNode *body, char *name) {
  ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
  if (!node) {
    fprintf(stderr, "Failed to allocate memory for function node\n");
    exit(EXIT_FAILURE);
  }
  node->type = AST_FUNCTION;
  node->data.function.body = body;
  node->data.function.name = name;
  node->next = NULL;
  return node;
}

// Create compound statement node
ASTNode *create_compound_stmt_node(ASTNode *stmts) {
  ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
  if (!node) {
    fprintf(stderr, "Failed to allocate memory for compound statement node\n");
    exit(EXIT_FAILURE);
  }
  node->type = AST_COMPOUND_STMT;
  node->data.compound_stmt.stmts = stmts;
  node->next = NULL;
  return node;
}

// Create declaration node
ASTNode *create_declaration_node(ASTNode *init_value, char *var_name) {
  ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
  if (!node) {
    fprintf(stderr, "Failed to allocate memory for declaration node\n");
    exit(EXIT_FAILURE);
  }
  node->type = AST_DECLARATION;
  node->data.declaration.init_value = init_value;
  node->data.declaration.var_name = var_name;
  node->next = NULL;
  return node;
}

// Create assignment node
ASTNode *create_assignment_node(ASTNode *value, char *var_name) {
  ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
  if (!node) {
    fprintf(stderr, "Failed to allocate memory for assignment node\n");
    exit(EXIT_FAILURE);
  }
  node->type = AST_ASSIGNMENT;
  node->data.assignment.value = value;
  node->data.assignment.var_name = var_name;
  node->next = NULL;
  return node;
}

// Create return node
ASTNode *create_return_node(ASTNode *value) {
  ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
  if (!node) {
    fprintf(stderr, "Failed to allocate memory for return node\n");
    exit(EXIT_FAILURE);
  }
  node->type = AST_RETURN;
  node->data.return_stmt.value = value;
  node->next = NULL;
  return node;
}

// Create binary operation node
ASTNode *create_binary_op_node(ASTNode *left, ASTNode *right, char op) {
  ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
  if (!node) {
    fprintf(stderr, "Failed to allocate memory for binary operation node\n");
    exit(EXIT_FAILURE);
  }
  node->type = AST_BINARY_OP;
  node->data.binary_op.left = left;
  node->data.binary_op.right = right;
  node->data.binary_op.op = op;
  node->next = NULL;
  return node;
}

// Create literal node
ASTNode *create_literal_node(int value) {
  ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
  if (!node) {
    fprintf(stderr, "Failed to allocate memory for literal node\n");
    exit(EXIT_FAILURE);
  }
  node->type = AST_LITERAL;
  node->data.literal.value = value;
  node->next = NULL;
  return node;
}

// Create identifier node
ASTNode *create_identifier_node(char *name) {
  ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
  if (!node) {
    fprintf(stderr, "Failed to allocate memory for identifier node\n");
    exit(EXIT_FAILURE);
  }
  node->type = AST_IDENTIFIER;
  node->data.identifier.name = name;
  node->next = NULL;
  return node;
}
void free_ast(ASTNode *node) {
  if (!node)
    return;

  switch (node->type) {
  case AST_PROGRAM:
    free_ast(node->data.program.functions);
    break;
  case AST_FUNCTION:
    free(node->data.function.name);
    free_ast(node->data.function.body);
    break;
  case AST_DECLARATION:
    free(node->data.declaration.var_name);
    free_ast(node->data.declaration.init_value);
    break;
  case AST_ASSIGNMENT:
    free(node->data.assignment.var_name);
    free_ast(node->data.assignment.value);
    break;
  case AST_RETURN:
    free_ast(node->data.return_stmt.value);
    break;
  case AST_BINARY_OP:
    free_ast(node->data.binary_op.left);
    free_ast(node->data.binary_op.right);
    break;
  case AST_LITERAL:
    // No dynamic memory to free
    break;
  case AST_IDENTIFIER:
    free(node->data.identifier.name);
    break;
  case AST_COMPOUND_STMT:
    free_ast(node->data.compound_stmt.stmts);
    break;
  default:
    break;
  }

  free_ast(node->next);
  free(node);
}
