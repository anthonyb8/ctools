#ifndef CVEC_H
#define CVEC_H

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

// Intial capacity if 8 is choosen somewhat arbitrarily.
static inline size_t grow_capacity(int capacity) {
  return (capacity < 8 ? 8 : capacity * 2);
}

// Count is the number of bytes to copy.
static inline void copy_mem(void* dest, void* src, size_t count) {
  memcpy(dest, src, count);
}

/**
 *  @brief Dynamic array container.
 */
typedef struct {
  void* data;        // Array
  size_t length;     // Number elements
  size_t capacity;   // Capacity for elements
  size_t elem_size;  // Byte size of each element
} Vec;

/**
 *  @brief Initialize a new Vec with no elemts
 *
 *  @param elem_size Size (in bytes) of the type to be stored.
 *
 *  @return Vec instance
 */
Vec vec_new(size_t elem_size);

/**
 *  @brief Initalizes Vec with values from an existing array. Values are copied
 *
 *  @param arr Values to make initial Vec.
 *  @param length Number of elements in arr.
 *  @param elem_size Size in bytes of each element.
 *
 *  @return Vec instance.
 */
Vec vec_from(void* arr, int length, size_t elem_size);

/**
 *  @brief Append element to the back of the array.
 *
 *  @param vec Pointer to Vec instance.
 *  @param item Pointer to element to be appended.
 */
void vec_push(Vec* vec, void* item);

/**
 *  @brief Retrieve element from array by index.
 *
 *  @param vec Pointer to Vec instance.
 *  @param index Position of item to be retrieved.
 *
 *  @return Pointer to object, NULL if out of range.
 */
void* vec_get(Vec* vec, int index);

/**
 *  @brief Remove and get last element.
 *
 *  @param vec Pointer to Vec instance.
 *  @param item Pointer where element will be allocated.
 *
 *  @return 0 on success, non-zero on failure
 */
int vec_pop(Vec* vec, void* item);

/**
 *  @brief View last element without removing.
 *
 *  @param vec Pointer to Vec instance.
 *
 *  @return Pointer to last element, memory manually managed as this can become
 * invalid if array altered.
 */
void* vec_peek(Vec* vec);

/**
 *  @brief Retrieve the number of elements in array.
 *
 *  @param vec Pointer to Vec instance.
 *
 *  @return Number of elements.
 */
int vec_len(Vec* vec);

/**
 *  @brief Destroy Vec instance, freeing memory.
 *
 *  @param vec Pointer to Vec instance.
 */
void freeVec(Vec* vec);

#endif
