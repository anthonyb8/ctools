#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
// Third party
#include <cmocka.h>

extern const struct CMUnitTest libTests[];
extern const size_t libTestsSize;

int main(void) {
  int failures = 0;
  failures +=
      _cmocka_run_group_tests("lib_tests", libTests, libTestsSize, NULL, NULL);
  return failures;
}
