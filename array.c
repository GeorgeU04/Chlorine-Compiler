#include "array.h"
#include "token.h"
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

const char *TokenTypeNames[] = {
    "TOKEN_NUMBER",  "TOKEN_IDENT", "TOKEN_KEYWORD",   "TOKEN_OPERATOR",
    "TOKEN_COMMENT", "TOKEN_DELIM", "TOKEN_SEMICOLON", "TOKEN_ERROR"};

void init_vector(vector **arr_ptr, uint32_t size) {
  vector *array;
  array = (vector *)malloc(sizeof(vector));
  if (!array) {
    printf("Memory allocation failed :(\n");
    exit(EXIT_FAILURE);
  }
  array->size = 0;
  array->capacity = size;
  array->array = (Token *)calloc(array->capacity, sizeof(Token));
  if (!array->array) {
    printf("Memory allocation failed :(\n");
    exit(EXIT_FAILURE);
  }
  *arr_ptr = array;
}

void print_vector(vector *array) {
  for (int32_t i = 0; i < array->size; ++i) {
    if (array->array[i].type == 7) {
      // printf("[ERROR] on line %d, Unkown Character\n", array->array[i].line);
    }
    printf("Value: %s | Type: %s | Line: %d\n", array->array[i].value,
           TokenTypeNames[array->array[i].type], array->array[i].line);
  }
}

void pushback(vector *array, Token value) {
  if (array->size == array->capacity) {
    array->capacity <<= 1;
    Token *temp =
        (Token *)realloc(array->array, sizeof(Token) * (array->capacity));
    if (!temp) {
      printf("Memory allocation failed :(\n");
      return;
    }
    array->array = temp;
  }
  array->array[array->size++] = value;
}

void free_vector(vector *array) {
  free(array->array);
  free(array);
}

Token *get_item(vector *array, int32_t index) {
  if (index >= array->size || index < 0) {
    printf("Index out of range silly goose\n");
    return NULL;
  }
  // printf("%s\n", array->array[index].value);
  return &array->array[index];
}

void insert(vector *array, Token value, int32_t index) {
  if (index > array->size || index < 0) {
    printf("Index out of range silly goose\n");
    return;
  }
  if (array->size == array->capacity) {
    array->capacity <<= 1;
    Token *temp =
        (Token *)realloc(array->array, sizeof(Token) * (array->capacity));
    if (!temp) {
      printf("Memory allocation failed :(\n");
      return;
    }
  }
  for (int32_t i = (int)array->size; i > index; --i) {
    array->array[i] = array->array[i - 1];
  }
  array->array[index] = value;
  array->size++;
}

void replace(vector *array, Token value, int32_t index) {
  if (index >= array->size || index < 0) {
    printf("Index out of range silly goose\n");
    return;
  }
  array->array[index] = value;
}

void delete_item(vector *array, int32_t index) {
  if (index > array->size || index < 0) {
    printf("Index out of range silly goose\n");
    return;
  }
  for (int32_t i = index; i < array->size - 1; ++i) {
    array->array[i] = array->array[i + 1];
  }
  array->size--;
}
