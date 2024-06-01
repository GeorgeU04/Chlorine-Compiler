#ifndef ARRAY_H
#define ARRAY_H

#include "token.h"
#include <stdint.h>
typedef struct vector {
  uint32_t size;
  uint32_t capacity;
  Token *array;
} vector;

void init_vector(vector **arr_ptr, int32_t size);

void pushback(vector *array, Token value);

void print_vector(vector *array);

void insert(vector *array, Token value, int32_t index);

void get_item(vector *array, int32_t index);

void delete_item(vector *array, int32_t index);

void free_vector(vector *array);

void replace(vector *array, Token value, int32_t index);

#endif
