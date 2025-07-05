#ifndef ctools_vec_h
#define ctools_vec_h

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

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
 *  @brief Initialize a Vec from an existing pointer.
 *
 *  @param vec Pointer to Vec.
 *  @param elem_size Byte size of each elements to be stored.
 */
void initVec(Vec* vec, size_t elem_size);

/**
 *  @brief Create a heap allocated Vec with no elements
 *
 *  @param elem_size Size (in bytes) of the type to be stored.
 *
 *  @return Pointer to Vec instance
 */
Vec* newVec(size_t elem_size);

/**
 *  @brief Create Vec with values from an existing array. Values are copied
 *
 *  @param arr Values to make initial Vec.
 *  @param length Number of elements in arr.
 *  @param elem_size Size in bytes of each element.
 *
 *  @return Vec instance.
 */
Vec fromArray(void* arr, int length, size_t elem_size);

/**
 *  @brief Append element to the back of the array.
 *
 *  @param vec Pointer to Vec instance.
 *  @param item Pointer to element to be appended.
 */
void vecPush(Vec* vec, void* item);

/**
 *  @brief Remove and get last element.
 *
 *  @param vec Pointer to Vec instance.
 *  @param item Pointer where element will be allocated.
 *
 *  @return 0 on success, non-zero on failure
 */
int vecPop(Vec* vec, void* item);

/**
 *  @brief Retrieve element from array by index.
 *
 *  @param vec Pointer to Vec instance.
 *  @param index Position of item to be retrieved.
 *
 *  @return Pointer to object, NULL if out of range.
 */
void* vecGet(Vec* vec, int index);

/**
 *  @brief Retrieve element from array by index.
 *
 *  @param vec Pointer to Vec instance.
 *  @param index Position of item to be retrieved.
 *
 *  @return Pointer to object, NULL if out of range.
 */
int vecSet(Vec* vec, int index, void* value);

/**
 *  @brief Retrieve the number of elements in array.
 *
 *  @param vec Pointer to Vec instance.
 *
 *  @return Number of elements.
 */
int vecLength(Vec* vec);

/**
 *  @brief Destroy Vec instance, freeing memory.
 *
 *  @param vec Pointer to Vec instance.
 */
void freeVec(Vec* vec);

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
VecIterator initVecIter(Vec* vec);

/**
 *  @brief Assign next element in Vec to passed pointer.
 *
 *  @param iter Pointer to VecIterator instance.
 *  @param item Pointer to be assigned to next item.
 *
 *  @return 0 on completion, non-zero otherwise.
 */
int vecNext(VecIterator* iter, void* item);

#endif
