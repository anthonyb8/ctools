#include <stddef.h>
#include <stdio.h>

#include "cvec/cvec.h"
#include "memory.h"

void vec_init(Vec* vec, size_t elem_size) {
  vec->data = NULL;
  vec->length = 0;
  vec->capacity = 0;
  vec->elem_size = elem_size;
};

Vec vec_new(size_t elem_size) {
  return (Vec){
      .data = NULL,
      .length = 0,
      .capacity = 0,
      .elem_size = elem_size,
  };
};

Vec vec_from(void* arr, int length, size_t elem_size) {
  if (arr == NULL) {
    return vec_new(elem_size);
  }

  void* data = malloc(length * elem_size);
  if (data == NULL) {
    exit(1);
  }

  copy_mem(data, arr, length * elem_size);
  return (Vec){.data = data,
               .length = length,
               .capacity = length,
               .elem_size = elem_size};
};

void vec_push(Vec* vec, void* item) {
  if (vec->length + 1 > vec->capacity) {
    size_t old_capacity = vec->capacity;
    vec->capacity = grow_capacity(old_capacity);
    vec->data = reallocate(vec->data, vec->elem_size * vec->capacity);
  }

  // Cast to char* for offset math only
  void* dest = (char*)vec->data + vec->length * vec->elem_size;

  copy_mem(dest, item, vec->elem_size);
  vec->length++;
}

void* vec_get(Vec* vec, int index) {
  if (index > vec->length || index < 0) {
    return NULL;
  }

  return (char*)vec->data + (vec->elem_size * index);
}

int vec_pop(Vec* vec, void* item) {
  if (vec->length == 0) {
    return 1;
  }

  vec->length--;

  // Cast to char* for offset math only
  void* src = (char*)vec->data + vec->length * vec->elem_size;
  copy_mem(item, src, vec->elem_size);

  return 0;
}

void* vec_peek(Vec* vec) {
  if (vec->length == 0) {
    return NULL;
  };

  return (char*)vec->data + (vec->length - 1) * vec->elem_size;
}

int vec_len(Vec* vec) { return vec->length; }

void freeVec(Vec* vec) { free(vec->data); }
