#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "ctools/vec.h"
#include "memory.h"

// iterator
void initVecIter(Vec* vec, VecIterator* iter) {
  iter->vec = vec;
  iter->index = 0;
  iter->current = (char*)vec->data;
};

VecIterator newVecIter(Vec* vec) {
  return (VecIterator){
      .vec = vec,
      .index = 0,
      .current = (char*)vec->data,
  };
}

void freeVecIter(VecIterator* iter) {
  iter->vec = NULL;
  iter->index = 0;
  iter->current = NULL;
}

void* vecNext(VecIterator* iter) {
  if (iter->index >= iter->vec->length) {
    return NULL;
  }

  void* current = iter->current;
  iter->index++;
  iter->current += iter->vec->elem_size;
  return current;
}

// Allocate
static inline void nullVec(Vec* vec, size_t elem_size) {
  vec->data = NULL;
  vec->length = 0;
  vec->capacity = 0;
  vec->elem_size = elem_size;
}

void initVec(Vec* vec, size_t elem_size) { nullVec(vec, elem_size); };

Vec newVec(size_t elem_size) {
  return (Vec){
      .data = NULL,
      .length = 0,
      .capacity = 0,
      .elem_size = elem_size,
  };
}

Vec fromArray(void* arr, int length, size_t elem_size) {
  if (arr == NULL) {
    return (Vec){
        .data = NULL,
        .length = 0,
        .capacity = 0,
        .elem_size = elem_size,
    };
  }

  void* dest = malloc(length * elem_size);
  if (dest == NULL) {
    exit(1);
  }
  memcpy(dest, arr, length * elem_size);

  return (Vec){.data = dest,
               .length = length,
               .capacity = length,
               .elem_size = elem_size};
};

void freeVec(Vec* vec) {
  free(vec->data);
  nullVec(vec, vec->elem_size);
}

// Updating
static inline void resize(Vec* vec) {
  size_t old_capacity = vec->capacity;
  vec->capacity = grow_capacity(old_capacity);
  vec->data = reallocate(vec->data, vec->elem_size * vec->capacity);
}

void vecPush(Vec* vec, void* item) {
  if (vec->length + 1 > vec->capacity) {
    resize(vec);
  }

  // Cast to char* for offset pointer math
  void* dest = (char*)vec->data + vec->length * vec->elem_size;
  memcpy(dest, item, vec->elem_size);

  vec->length++;
}

int vecPop(Vec* vec, void* item) {
  if (vec->length == 0) {
    return 1;
  }

  vec->length--;

  // Cast to char* for offset pointer math
  void* src = (char*)vec->data + vec->length * vec->elem_size;
  memcpy(item, src, vec->elem_size);

  return 0;
}

void* vecGet(Vec* vec, int index) {
  if (index > vec->length || index < 0) {
    return NULL;
  }

  return (char*)vec->data + (vec->elem_size * index);
}

int vecSet(Vec* vec, int index, void* value) {
  if (vec->length < index - 1 || index < 0) {
    return 1;
  }

  if (vec->length == index) {
    vecPush(vec, value);
  }

  void* src = (char*)vec->data + index * vec->elem_size;
  memcpy(src, value, vec->elem_size);

  return 0;
}

int vecLength(Vec* vec) { return vec->length; }
