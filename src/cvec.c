#include <stdio.h>

#include "cvec/cvec.h"
#include "memory.h"

VecIterator init_vec_iter(Vec* vec) {
  return (VecIterator){
      .vec = vec,
      .index = 0,
      .current = (char*)vec->data,
  };
}

int next(VecIterator* iter, void* item) {
  if (iter->index >= iter->vec->length) {
    return 0;
  }

  memcpy(item, iter->current, iter->vec->elem_size);
  iter->index++;
  iter->current += iter->vec->elem_size;
  return 1;
}

Vec vec_new(size_t elem_size) {
  return (Vec){
      .data = NULL,
      .length = 0,
      .capacity = 0,
      .elem_size = elem_size,
  };
}

Vec vec_from(void* arr, int length, size_t elem_size) {
  if (arr == NULL) {
    return vec_new(elem_size);
  }

  void* data = malloc(length * elem_size);
  if (data == NULL) {
    exit(1);
  }

  memcpy(data, arr, length * elem_size);
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
  char* base = (char*)vec->data;
  memcpy(base + vec->length * vec->elem_size, item, vec->elem_size);

  vec->length++;
}

void* vec_get(Vec* vec, int index) {
  if (index > vec->length || index < 0) {
    return NULL;
  }
  char* base = (char*)vec->data;
  return base + (vec->elem_size * index);
}

int vec_pop(Vec* vec, void* item) {
  if (vec->length == 0) {
    return 1;
  }

  vec->length--;

  char* base = (char*)vec->data;
  memcpy(item, base + vec->length * vec->elem_size, vec->elem_size);

  return 0;
}

void* vec_peek(Vec* vec) {
  if (vec->length == 0) return NULL;
  char* base = (char*)vec->data;
  return base + (vec->length - 1) * vec->elem_size;
}

int vec_len(Vec* vec) { return vec->length; }

void freeVec(Vec* vec) { free(vec->data); }
