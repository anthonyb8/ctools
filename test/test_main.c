#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
// Third party
#include <cmocka.h>

extern const struct CMUnitTest vecTests[];
extern const size_t vecTestsSize;

extern const struct CMUnitTest mapTests[];
extern const size_t mapTestsSize;

int main(void) {
  int failures = 0;
  failures +=
      _cmocka_run_group_tests("vec_tests", vecTests, vecTestsSize, NULL, NULL);

  failures +=
      _cmocka_run_group_tests("map_tests", mapTests, mapTestsSize, NULL, NULL);
  return failures;
}
