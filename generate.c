#include "generate.h"
#include "ast.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *output = NULL;

void close_output() {
  if (output != NULL) {
    fclose(output);
    output = NULL;
  }
}

void open_output(const char *file) {
  output = fopen(file, "w");
  if (output == NULL) {
    fprintf(stderr, "[ERROR] Could not open output file\n");
    exit(EXIT_FAILURE);
  }
  emit("section .bss\n");
}

void emit(const char *format, ...) {
  if (output == NULL) {
    fprintf(stderr, "[ERROR] Output file is not open\n");
    exit(EXIT_FAILURE);
  }

  va_list args;
  va_start(args, format);
  vfprintf(output, format, args);
  va_end(args);
}

void generate_function_declaration(ASTNode *function) {
  if (strcmp(function->data.function.name, "main") == 0) {
    emit("section .text\nglobal _start\n\n_start:\n");
    generate_statements(function->data.function.body);
  }
}

void generate_return_statement(ASTNode *returnStmt) {
  generate_expression(returnStmt->data.return_stmt.value);
  emit("ret\n");
}

void generate_variable_declaration(ASTNode *declaration) {
  emit("%s: resb 4\n", declaration->data.declaration.var_name);
}

void generate_assignment_statement(ASTNode *assignment) {
  generate_expression(assignment->data.assignment.value);
  emit("mov [%s], rax\n", assignment->data.assignment.var_name);
}

void generate_expression(ASTNode *expression) {
  switch (expression->type) {
  case AST_LITERAL:
    emit("mov rax, %d\n", expression->data.literal.value);
    break;
  case AST_IDENTIFIER:
    emit("mov rax, %s\n", expression->data.identifier.name);
    emit("mov rax, [%s]\n", expression->data.identifier.name);
    break;
  default:
    handle_error(expression);
    break;
  }
}

void generate_statements(ASTNode *statements) {
  while (statements != NULL) {
    switch (statements->type) {
    case AST_ASSIGNMENT:
      generate_assignment_statement(statements);
      break;
    case AST_RETURN:
      generate_return_statement(statements);
      break;
    case AST_FUNCTION:
      generate_function_declaration(statements);
      break;
    case AST_DECLARATION:
      generate_variable_declaration(statements);
      break;
    case AST_PROGRAM:
      generate_statements(statements->data.program.functions);
      break;
    default:
      handle_error(statements);
      break;
    }
    statements = statements->next;
  }
}

void handle_error(ASTNode *error) {
  fprintf(stderr, "Error: Unexpected AST node type %d\n", error->type);
  exit(EXIT_FAILURE);
}
