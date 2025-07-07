#include <stdio.h>
#include <string.h>

#include "ctools/comparators.h"

#define CMP_FUNCTION(TYPE)                        \
  bool TYPE##_cmp(const void* a, const void* b) { \
    return *(const TYPE*)a == *(const TYPE*)b;    \
  }

CMP_FUNCTION(int)
CMP_FUNCTION(long)
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

#define PRINT_FUNCTION(NAME, TYPE, FORMATTER) \
  void NAME##_print(const void* value) {      \
    printf(FORMATTER, *(const TYPE*)value);   \
  }

PRINT_FUNCTION(int, int, "%d")
PRINT_FUNCTION(long, long, "%lu")
PRINT_FUNCTION(byte, size_t, "%lu")
PRINT_FUNCTION(bool, bool, "%d")
PRINT_FUNCTION(char, char, "%c")
PRINT_FUNCTION(double, double, "%f")
PRINT_FUNCTION(float, float, "%f")
PRINT_FUNCTION(str, char*, "%s")
