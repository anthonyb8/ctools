#ifndef COMPARATORS_H
#define COMPARATORS_H

#include <stdbool.h>

bool int_cmp(const void* a, const void* b);
bool long_cmp(const void* a, const void* b);
bool size_t_cmp(const void* a, const void* b);
bool bool_cmp(const void* a, const void* b);
bool float_cmp(const void* a, const void* b);
bool double_cmp(const void* a, const void* b);
bool char_cmp(const void* a, const void* b);
bool str_cmp(const void* a, const void* b);

#define CMP_INT int_cmp
#define CMP_LONG long_cmp
#define CMP_UINT uint_cmp
#define CMP_SIZE_T size_t_cmp
#define CMP_BOOL bool_cmp
#define CMP_FLOAT float_cmp
#define CMP_DOUBLE double_cmp
#define CMP_CHAR char_cmp
#define CMP_STR str_cmp

void int_print(const void* value);
void long_print(const void* value);
void size_t_print(const void* value);
void bool_print(const void* value);
void float_print(const void* value);
void double_print(const void* value);
void char_print(const void* value);
void str_print(const void* value);

#define PRINT_INT int_print
#define PRINT_LONG long_print
#define PRINT_STR str_print
#define PRINT_BYTE byte_print
#define PRINT_CHAR char_print
#define PRINT_SIZE_T size_t_print
#define PRINT_BOOL bool_print
#define PRINT_DOUBLE double_print
#define PRINT_FLOAT float_print

#endif  // COMPARATORS_H
