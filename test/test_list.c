#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

// Third party
#include <cmocka.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ctools/list.h"

// Int
#define CMP_INT CMP_FUNCTION(int)
#define PRINT_INT PRINT_FUNCTION(int, "%d")

// String
#define CMP_STR CMP_FUNCTION(char*)
#define PRINT_STR PRINT_FUNCTION(char*, "%s")

// Structs
typedef struct {
  int a;
  char b;
  double c;
} Dummy;

bool compareDummy(Dummy* a, Dummy* b) {
  if (a->a != b->a) {
    return false;
  }

  if (a->b != b->b) {
    return false;
  }

  if (a->c != b->c) {
    return false;
  }

  return true;
}

bool cmpDummy(const void* a, const void* b) {
  return compareDummy((Dummy*)a, (Dummy*)b);
}
void printDummy(const void* value) {
  Dummy* d = (Dummy*)value;
  printf("{a:%d, b:%c, c:%f", d->a, d->b, d->c);
};

// Tests
static void test_list_int(void** state) {
  (void)state;

  Node* node;
  // initNode(&node);
}

static void test_list_int2(void** state) {
  (void)state;

  // List list;
  // initList(&list, cmpInt, printInt);
  //
  // // Inserts
  // for (int i = 0; i < 10; i++) {
  //   int* value = malloc(sizeof(int));
  //   *value = i;
  //   insertHead(&list, value);
  // }
  //
  // for (int i = 10; i < 20; i++) {
  //   int* value = malloc(sizeof(int));
  //   *value = i;
  //   insertTail(&list, value);
  // }
  //
  // int g = 99;
  // insertAt(&list, 9, &g);
  //
  // // Get
  // int* d = (int*)getHead(&list)->value;
  // printf("Head : %d\n", *d);
  //
  // int* e = (int*)getTail(&list)->value;
  // printf("Tail : %d\n", *e);
  //
  // int p = 8;
  // Node* node = find(&list, &p);
  // printf("Value : %d | Next Value: %d\n", *(int*)node->value,
  //        *(int*)node->next->value);
  //
  // // Delete
  // deleteHead(&list);
  // deleteTail(&list);
  // deleteValue(&list, node->next->value);
}

static void test_list_string(void** state) {
  (void)state;

  // List list;
  // initList(&list, cmpInt, printInt);
  //
  // // Inserts
  // for (int i = 0; i < 10; i++) {
  //   int* value = malloc(sizeof(int));
  //   *value = i;
  //   insertHead(&list, value);
  // }
  //
  // for (int i = 10; i < 20; i++) {
  //   int* value = malloc(sizeof(int));
  //   *value = i;
  //   insertTail(&list, value);
  // }
  //
  // int g = 99;
  // insertAt(&list, 9, &g);
  //
  // // Get
  // int* d = (int*)getHead(&list)->value;
  // printf("Head : %d\n", *d);
  //
  // int* e = (int*)getTail(&list)->value;
  // printf("Tail : %d\n", *e);
  //
  // int p = 8;
  // Node* node = find(&list, &p);
  // printf("Value : %d | Next Value: %d\n", *(int*)node->value,
  //        *(int*)node->next->value);
  //
  // // Delete
  // deleteHead(&list);
  // deleteTail(&list);
  // deleteValue(&list, node->next->value);
}

static void test_list_struct(void** state) {
  (void)state;

  // List list;
  // initList(&list, cmpInt, printInt);
  //
  // // Inserts
  // for (int i = 0; i < 10; i++) {
  //   int* value = malloc(sizeof(int));
  //   *value = i;
  //   insertHead(&list, value);
  // }
  //
  // for (int i = 10; i < 20; i++) {
  //   int* value = malloc(sizeof(int));
  //   *value = i;
  //   insertTail(&list, value);
  // }
  //
  // int g = 99;
  // insertAt(&list, 9, &g);
  //
  // // Get
  // int* d = (int*)getHead(&list)->value;
  // printf("Head : %d\n", *d);
  //
  // int* e = (int*)getTail(&list)->value;
  // printf("Tail : %d\n", *e);
  //
  // int p = 8;
  // Node* node = find(&list, &p);
  // printf("Value : %d | Next Value: %d\n", *(int*)node->value,
  //        *(int*)node->next->value);
  //
  // // Delete
  // deleteHead(&list);
  // deleteTail(&list);
  // deleteValue(&list, node->next->value);
}

const struct CMUnitTest listTests[] = {cmocka_unit_test(test_list_int)};

const size_t listTestsSize = sizeof(listTests) / sizeof(listTests[0]);
