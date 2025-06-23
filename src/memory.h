#ifndef CVEC_MEMORY_H
#define CVEC_MEMORY_H

#include <stdlib.h>

// Adjusts memory of a array based on new_size, freeing if the new size is 0.
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
