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
  Vec vec = newVec(sizeof(int));
  assert_int_equal(vecLength(&vec), 0);

  freeVec(&vec);
}

static void test_memory(void **state) {
  (void)state;

  int arr[] = {0, 1, 2, 3, 4, 5, 6};

  Vec vec = fromArray(&arr, sizeof(arr) / sizeof(arr[0]), sizeof(arr[0]));
  assert_int_equal(vecLength(&vec), 7);

  vecPush(&vec, &(int){7});
  vecPush(&vec, &(int){8});
  vecPush(&vec, &(int){9});

  VecIterator iter = newVecIter(&vec);
  char *last = NULL;
  int last_value = 0;

  // Memory check (assumes int in 4 bytes)
  for (void *v = vecNext(&iter); v != NULL; v = vecNext(&iter)) {
    if (last != NULL) {
      int diff_mem = (char *)v - last;
      assert_int_equal(diff_mem, 4);

      int diff_val = *(int *)v - last_value;
      assert_int_equal(diff_val, 1);
    }
    last = (char *)v;
    last_value = *(int *)v;
  }

  freeVecIter(&iter);
  freeVec(&vec);
}

static void test_from(void **state) {
  (void)state;

  int arr[] = {0, 1, 2, 4, 5, 8, 9};

  Vec vec = fromArray(&arr, sizeof(arr) / sizeof(int), sizeof(int));
  assert_int_equal(vecLength(&vec), 7);

  freeVec(&vec);
}

static void test_push(void **state) {
  (void)state;

  Vec vec = newVec(sizeof(int));

  // Push
  int x = 6;
  vecPush(&vec, &x);

  // Test
  assert_int_equal(vecLength(&vec), 1);

  freeVec(&vec);
}

static void test_length(void **state) {
  (void)state;

  int arr[] = {0, 1, 2, 4, 5, 8, 9};
  Vec vec = fromArray(&arr, sizeof(arr) / sizeof(int), sizeof(int));

  // Length
  int length = vecLength(&vec);

  // Test
  assert_int_equal(vecLength(&vec), 7);
  freeVec(&vec);
}

static void test_get(void **state) {
  (void)state;

  int arr[] = {0, 1, 2, 4, 5, 8, 9};
  Vec vec = fromArray(&arr, sizeof(arr) / sizeof(int), sizeof(int));

  // Get
  int *gotten = vecGet(&vec, 5);

  // Test
  assert_int_equal(*gotten, 8);
  freeVec(&vec);
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
  freeVec(&vec);
}

static void test_iterator(void **state) {
  (void)state;

  int arr[] = {0, 1, 2, 4, 5, 8, 9};
  Vec vec = fromArray(&arr, sizeof(arr) / sizeof(int), sizeof(int));

  // Iter
  VecIterator iter = newVecIter(&vec);

  int value;
  int i = 0;
  // while (vecNext(&iter, &value)) {
  //   assert_int_equal(arr[i], value);
  //   i++;
  // }
}

const struct CMUnitTest vecTests[] = {
    cmocka_unit_test(test_new),      cmocka_unit_test(test_from),
    cmocka_unit_test(test_push),     cmocka_unit_test(test_pop),
    cmocka_unit_test(test_get),      cmocka_unit_test(test_length),
    cmocka_unit_test(test_iterator), cmocka_unit_test(test_memory)};
const size_t vecTestsSize = sizeof(vecTests) / sizeof(vecTests[0]);
