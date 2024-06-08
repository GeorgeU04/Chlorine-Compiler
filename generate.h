#ifndef GENERATE_H
#define GENERATE_H

#include "ast.h"
#include <stdio.h>
void generate_function_declaration(ASTNode *function);
void generate_return_statement(ASTNode *returnStmt);
void generate_variable_declaration(ASTNode *declaration);
void generate_assignment_statement(ASTNode *assignment);
void generate_expression(ASTNode *expression);
void generate_conditional_statement(ASTNode *conditionalStmt);
void generate_loop_statement(ASTNode *loopStmt);
void generate_function_call(ASTNode *functionCall);
void generate_memory_access(ASTNode *memoryAccess);
void handle_error(ASTNode *error);
void emit(const char *format, ...);
void generate_statements(ASTNode *statements);
void close_output();
void open_output(const char *file);
#endif
