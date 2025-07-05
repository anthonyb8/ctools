#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

// Third party
#include <cmocka.h>

#include "ctools/vec.h"

static void test_new(void **state) {
  (void)state;

  // New
  Vec *vec = newVec(sizeof(int));
  assert_int_equal(vecLength(vec), 0);
}

static void test_from(void **state) {
  (void)state;

  int arr[] = {0, 1, 2, 4, 5, 8, 9};

  Vec vec = fromArray(&arr, sizeof(arr) / sizeof(int), sizeof(int));
  assert_int_equal(vecLength(&vec), 7);
}

static void test_push(void **state) {
  (void)state;

  Vec *vec = newVec(sizeof(int));

  // Push
  int x = 6;
  vecPush(vec, &x);

  // Test
  assert_int_equal(vecLength(vec), 1);
}

static void test_length(void **state) {
  (void)state;

  int arr[] = {0, 1, 2, 4, 5, 8, 9};
  Vec vec = fromArray(&arr, sizeof(arr) / sizeof(int), sizeof(int));

  // Length
  int length = vecLength(&vec);

  // Test
  assert_int_equal(vecLength(&vec), 7);
}

static void test_get(void **state) {
  (void)state;

  int arr[] = {0, 1, 2, 4, 5, 8, 9};
  Vec vec = fromArray(&arr, sizeof(arr) / sizeof(int), sizeof(int));

  // Get
  int *gotten = vecGet(&vec, 5);

  // Test
  assert_int_equal(*gotten, 8);
}

// static void test_peek(void **state) {
//   (void)state;
//
//   int arr[] = {0, 1, 2, 4, 5, 8, 9};
//   Vec vec = fromArray(&arr, sizeof(arr) / sizeof(int), sizeof(int));
//
//   // Peek
//   void *val = vecPeek(&vec);
//
//   // Test
//   assert_int_equal(*(int *)val, 9);
// }

static void test_pop(void **state) {
  (void)state;

  int arr[] = {0, 1, 2, 4, 5, 8, 9};
  Vec vec = fromArray(&arr, sizeof(arr) / sizeof(int), sizeof(int));

  // Pop
  int popped;
  int status = vecPop(&vec, &popped);

  // Test
  assert_int_equal(popped, 9);
  assert_int_equal(vecLength(&vec), 6);
}

static void test_iterator(void **state) {
  (void)state;

  int arr[] = {0, 1, 2, 4, 5, 8, 9};
  Vec vec = fromArray(&arr, sizeof(arr) / sizeof(int), sizeof(int));

  // Iter
  VecIterator iter = initVecIter(&vec);

  int value;
  int i = 0;
  while (vecNext(&iter, &value)) {
    assert_int_equal(arr[i], value);
    i++;
  }
}

const struct CMUnitTest vecTests[] = {
    cmocka_unit_test(test_new),     cmocka_unit_test(test_from),
    cmocka_unit_test(test_push),    cmocka_unit_test(test_pop),
    cmocka_unit_test(test_get),     cmocka_unit_test(test_length),
    cmocka_unit_test(test_iterator)};
const size_t vecTestsSize = sizeof(vecTests) / sizeof(vecTests[0]);
