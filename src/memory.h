#ifndef CTOOLS_MEMORY_H
#define CTOOLS_MEMORY_H

#include <stdlib.h>
#include <string.h>

#define FREE_ARRAY(type, pointer) reallocate(pointer, 0)

// Intial capacity if 8 is choosen somewhat arbitrarily.
static inline size_t grow_capacity(int capacity) {
  return (capacity < 8 ? 8 : capacity * 2);
}

// Count is the number of bytes to copy.
static inline void copy_mem(void* dest, void* src, size_t count) {
  memcpy(dest, src, count);
}

// Adjusts memory of a array based on new_size, freeing if the new size is 0.
static inline void* reallocate(void* ptr, size_t new_size) {
  if (new_size == 0) {
    free(ptr);
    return NULL;
  }
  void* new_ptr = realloc(ptr, new_size);

  if (new_ptr == NULL) {
    exit(1);
  }
  return new_ptr;
}

#endif
