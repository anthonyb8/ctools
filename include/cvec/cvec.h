#ifndef CVEC_H
#define CVEC_H

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

static inline size_t grow_capacity(int capacity) {
  return (capacity < 8 ? 8 : capacity * 2);
}

// Dynamic array struct.
typedef struct {
  void* data;
  size_t length;
  size_t capacity;
  size_t elem_size;
} Vec;

typedef struct {
  Vec* vec;
  size_t index;
  char* current;
} VecIterator;

VecIterator init_vec_iter(Vec* vec);
int next(VecIterator* iter, void* item);

// Initialize a new empty vec
Vec vec_new(size_t elem_size);

// Initialize a new vec from an existing array
// Array is copied not referenced
Vec vec_from(void* arr, int length, size_t elem_size);

// Appends item to the end of the vec
void vec_push(Vec* vec, void* item);

// Retrieve item from vec by index.
// Returns:
//  - 0: Success
//  - 1: Failure
void* vec_get(Vec* vec, int index);

// Remove last item from the vec, item is copied to void*.
int vec_pop(Vec* vec, void* item);

// Returns pointer to internal value, can be invalidated
// if array vec is updated
void* vec_peek(Vec* vec);

// Returns number of items in the vec.
int vec_len(Vec* vec);

// Free memory allocated to the vec.
void freeVec(Vec* vec);

// Delete later
void vec_iter(Vec* vec);

#endif
