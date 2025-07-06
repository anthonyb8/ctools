#ifndef COMPARATORS_H
#define COMPARATORS_H

#include <stdbool.h>

bool int_cmp(const void* a, const void* b);
bool long_cmp(const void* a, const void* b);
bool uint_cmp(const void* a, const void* b);
bool size_t_cmp(const void* a, const void* b);
bool bool_cmp(const void* a, const void* b);
bool float_cmp(const void* a, const void* b);
bool double_cmp(const void* a, const void* b);
bool char_cmp(const void* a, const void* b);
bool str_cmp(const void* a, const void* b);

// Macros for convenience:
#define CMP_INT int_cmp
#define CMP_LONG long_cmp
#define CMP_UINT uint_cmp
#define CMP_SIZE_T size_t_cmp
#define CMP_BOOL bool_cmp
#define CMP_FLOAT float_cmp
#define CMP_DOUBLE double_cmp
#define CMP_CHAR char_cmp
#define CMP_STR str_cmp

#endif  // COMPARATORS_H
