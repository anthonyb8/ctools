#ifndef CVEC_ITERATOR_H
#define CVEC_ITERATOR_H

#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#include "cvec.h"

/**
 *  @brief Iterator to traverse a Vec instance.
 */
typedef struct {
  Vec* vec;       // Pointer to the Vec being iterated
  size_t index;   // Current index in the Vec
  char* current;  // Pointer to current element
} VecIterator;

/**
 *  @brief Initialize VecIterator instance.
 *
 *  @param vec Pointer to Vec instance.
 *
 *  @return VecIterator instance.
 */
VecIterator init_vec_iter(Vec* vec);

/**
 *  @brief Assign next element in Vec to passed pointer.
 *
 *  @param iter Pointer to VecIterator instance.
 *  @param item Pointer to be assigned to next item.
 *
 *  @return 0 on completion, non-zero otherwise.
 */
int next(VecIterator* iter, void* item);

#endif
