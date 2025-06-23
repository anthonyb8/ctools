#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

// Third party
#include <cmocka.h>

#include "cvec/cvec.h"

static void test_new(void **state) {
  (void)state;

  // New
  Vec vec = vec_new(sizeof(int));
  assert_int_equal(vec_len(&vec), 1);
}

static void test_from(void **state) {
  (void)state;

  int arr[] = {0, 1, 2, 4, 5, 8, 9};

  Vec vec = vec_from(&arr, sizeof(arr) / sizeof(int), sizeof(int));
  assert_int_equal(vec_len(&vec), 7);
}

const struct CMUnitTest libTests[] = {cmocka_unit_test(test_new),
                                      cmocka_unit_test(test_from)};
const size_t libTestsSize = sizeof(libTests) / sizeof(libTests[0]);
