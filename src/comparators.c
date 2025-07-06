#include <stdio.h>
#include <string.h>

#include "ctools/comparators.h"

// Macro to define comparator functions
#define CMP_FUNCTION(TYPE)                        \
  bool TYPE##_cmp(const void* a, const void* b) { \
    return *(const TYPE*)a == *(const TYPE*)b;    \
  }

// Instantiate functions
CMP_FUNCTION(int)
CMP_FUNCTION(long)
// CMP_FUNCTION(uint)
CMP_FUNCTION(size_t)
CMP_FUNCTION(bool)
CMP_FUNCTION(float)
CMP_FUNCTION(double)
CMP_FUNCTION(char)

bool str_cmp(const void* a, const void* b) {
  const char* sa = (const char*)a;
  const char* sb = (const char*)b;
  return strcmp(sa, sb) == 0;
}
