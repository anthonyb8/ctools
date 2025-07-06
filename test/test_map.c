#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

// Third party
#include <cmocka.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ctools/map.h"

void fillMap(Map* map, int count) {
  for (int i = 0; i < count; i++) {
    char kbuf[2] = {'a' + i, '\0'};
    char* key = strdup(kbuf);

    int* value = malloc(sizeof(int));
    *value = i;

    mapPut(map, key, value);
  }
}

// Tests
// Cant test by jumping beacues value  aren  back to back persa inth  aray
static void test_map_mem(void** state) {
  (void)state;

  Map map = newMap(2, sizeof(int), CMP_STR);
  fillMap(&map, 7);

  MapIterator iter = newMapIter(&map);
  char* last = NULL;
  int last_value = 0;

  for (void* v = mapNext(&iter); v != NULL; v = mapNext(&iter)) {
    if (last != NULL) {
      // printf("%p\n", v);
    }
    last = (char*)v;
    last_value = *(int*)(v + 2);
  }

  freeMapIter(&iter);

  // Test
  freeMap(&map);
}

static void test_map_get(void** state) {
  (void)state;

  // Map map;
  Map map = newMap(10, sizeof(int), CMP_STR);

  // Set
  char* key = "apple";
  int value = 4000;

  // Test
  bool newKey = mapPut(&map, key, &value);

  // Get
  void* entry = mapGet(&map, key);
  if (entry == NULL) {
    printf("Entry shouldn't be null\n ");
  }

  // Check
  assert_int_equal(*(int*)entry, value);

  // Free
  freeMap(&map);
}

static void test_map_clear(void** state) {
  (void)state;

  Map map = newMap(10, sizeof(int), CMP_STR);

  // Set
  char* key = "apple";
  int value = 1;
  bool newKey = mapPut(&map, key, &value);

  // Get
  void* entry1 = mapGet(&map, key);
  if (entry1 == NULL) {
    printf("Entry shouldn't be null\n ");
  }
  assert_int_equal(*(int*)entry1, value);

  // Clear
  mapClear(&map);
  void* entry2 = mapGet(&map, key);
  assert_ptr_equal(entry2, NULL);

  // Free
  freeMap(&map);
}

static void test_map_free(void** state) {
  (void)state;

  Map map = newMap(10, sizeof(int), CMP_STR);

  // Set
  char* key = "apple";
  int value = 1;
  bool newKey = mapPut(&map, key, &value);

  // Get
  void* entry1 = mapGet(&map, key);
  if (entry1 == NULL) {
    printf("Entry shouldn't be null\n ");
  }
  assert_int_equal(*(int*)entry1, value);

  // Test
  freeMap(&map);

  // Validate
  assert_int_not_equal(*(int*)entry1, value);  // entry1 value gone
}

static void test_map_remove(void** state) {
  (void)state;

  Map map = newMap(10, sizeof(int), CMP_STR);

  // Set
  char* key = "apple";
  int value = 1;
  bool newKey = mapPut(&map, key, &value);

  // Get
  void* entry = mapGet(&map, key);
  if (entry == NULL) printf("Entry shouldn't be null\n ");
  assert_int_equal(*(int*)entry, value);

  // Test
  mapRemove(&map, key);

  // Validate
  void* entryGone = mapGet(&map, key);
  assert_ptr_equal(entryGone, NULL);

  // Cleanup
  freeMap(&map);
}

static void test_map_remove_add_back(void** state) {
  (void)state;

  Map map = newMap(10, sizeof(int), CMP_STR);

  // Set
  char* key = "apple";
  int value = 1;
  bool newKey = mapPut(&map, key, &value);
  assert_int_equal(map.count, 1);

  // Delete
  mapRemove(&map, key);
  assert_int_equal(map.count, 1);

  // Test
  int value2 = 1000;
  bool new = mapPut(&map, key, &value2);

  // Validate
  void* entry = mapGet(&map, key);
  if (entry == NULL) printf("Entry shouldn't be null\n ");

  assert_int_equal(*(int*)entry, value2);
  assert_int_equal(map.count, 1);

  // Cleanup
  freeMap(&map);
}

static void test_map_size(void** state) {
  (void)state;

  Map map = newMap(12, sizeof(int), CMP_STR);

  // seed
  int length = 8;
  fillMap(&map, length);

  // Validate
  assert_int_equal(mapSize(&map), length);

  // Cleanup
  freeMap(&map);
}

static void test_map_contains(void** state) {
  (void)state;

  Map map = newMap(12, sizeof(int), CMP_STR);

  // seed
  int length = 8;
  fillMap(&map, length);

  // Validate
  for (int i = 0; i < length; i++) {
    char kbuf[2] = {'a' + i, '\0'};
    char* key = strdup(kbuf);

    int* value = malloc(sizeof(int));
    *value = i;

    assert_true(mapContains(&map, key));
  }

  // Cleanup
  freeMap(&map);
}

const struct CMUnitTest mapTests[] = {
    cmocka_unit_test(test_map_get),
    cmocka_unit_test(test_map_clear),
    cmocka_unit_test(test_map_free),
    cmocka_unit_test(test_map_remove),
    cmocka_unit_test(test_map_remove_add_back),
    cmocka_unit_test(test_map_size),
    cmocka_unit_test(test_map_contains),
    cmocka_unit_test(test_map_mem)};

const size_t mapTestsSize = sizeof(mapTests) / sizeof(mapTests[0]);
