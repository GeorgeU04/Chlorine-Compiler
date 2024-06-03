#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "array.h"
#include "stdio.h"

vector *tokenize(FILE *file, vector *token_array);
bool check_for_keyword(const char *str);

#endif
