#ifndef CVEC_MEMORY_H
#define CVEC_MEMORY_H

#include <stdlib.h>

void* reallocate(void* ptr, size_t new_size) {
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

#endif  // !CVEC_MEMORY_H
