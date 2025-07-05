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

    mapPut(map, key, strlen(key), value, sizeof(int));
  }
}

// Tests
static void test_entry_free(void** state) {
  (void)state;

  char* key = "key";
  int value = 10000;

  // Entry
  Entry entry;
  initEntry(&entry, key, strlen(key), &value, sizeof(int));

  // Store for free check
  char* entryKey = entry.key;
  int* entryValue = entry.value;

  // Values the same
  assert_int_equal(value, *entryValue);
  assert_string_equal(key, entryKey);

  // Pointer different
  assert_ptr_not_equal(&value, entryValue);
  assert_ptr_not_equal(&key, entryKey);

  // Should free internal memory
  freeEntry(&entry);

  // Values cleared
  assert_int_not_equal(value, *entryValue);
  assert_string_not_equal(key, entryKey);
}

static void test_entry_reassign(void** state) {
  (void)state;

  char* key = "key";
  int value = 10000;

  // Entry
  Entry entry;
  initEntry(&entry, key, strlen(key), &value, sizeof(int));

  // Store for reassigned check
  char* entryKey = entry.key;
  int* entryValue = entry.value;

  // Check values as expected
  assert_int_equal(value, *(int*)entry.value);
  assert_string_equal(key, entry.key);
  assert_ptr_not_equal(&value, entry.value);
  assert_ptr_not_equal(&key, entry.key);

  // Reassign Entry values
  char* key2 = "ke2y";
  int value2 = 10001;
  reassignEntry(&entry, key2, strlen(key2), &value2, sizeof(int));

  // Old values free
  assert_string_not_equal(key, entryKey);
  assert_int_not_equal(value, *entryValue);

  // New values
  assert_int_equal(value2, *(int*)entry.value);
  assert_string_equal(key2, entry.key);
  assert_ptr_not_equal(&value2, entry.value);
  assert_ptr_not_equal(&key2, entry.key);

  // Clean up
  freeEntry(&entry);
}

static void test_entry_reassign_same_key(void** state) {
  (void)state;

  char* key = "key";
  int value = 10000;

  // Entry
  Entry entry;
  initEntry(&entry, key, strlen(key), &value, sizeof(int));

  // Store for reassigned check
  char* entryKey = entry.key;
  int* entryValue = entry.value;

  // Check values as expected
  assert_int_equal(value, *(int*)entry.value);
  assert_string_equal(key, entry.key);
  assert_ptr_not_equal(&value, entry.value);
  assert_ptr_not_equal(&key, entry.key);

  // Reassign Entry values
  int value2 = 10001;
  reassignEntry(&entry, key, strlen(key), &value2, sizeof(int));

  // Old values free
  assert_int_not_equal(value, *entryValue);

  // New values
  assert_int_equal(value2, *(int*)entry.value);
  assert_string_equal(key, entry.key);

  assert_ptr_not_equal(&value2, entry.value);
  assert_ptr_not_equal(&key, entry.key);
  assert_ptr_equal(entry.key, entryKey);

  // Clean up
  freeEntry(&entry);
}

static void test_map_get(void** state) {
  (void)state;

  Map map;
  initMap(&map);

  // Set
  char* key = "apple";
  int value = 1;

  // Test
  bool newKey = mapPut(&map, key, strlen(key) + 1, &value, sizeof(int));

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

  Map map;
  initMap(&map);

  // Set
  char* key = "apple";
  int value = 1;
  bool newKey = mapPut(&map, key, strlen(key) + 1, &value, sizeof(int));

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

  Map map;
  initMap(&map);

  // Set
  char* key = "apple";
  int value = 1;
  bool newKey = mapPut(&map, key, strlen(key) + 1, &value, sizeof(int));

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

  Map map;
  initMap(&map);

  // Set
  char* key = "apple";
  int value = 1;
  bool newKey = mapPut(&map, key, strlen(key) + 1, &value, sizeof(int));

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

  Map map;
  initMap(&map);

  // Set
  char* key = "apple";
  int value = 1;
  bool newKey = mapPut(&map, key, strlen(key) + 1, &value, sizeof(int));
  assert_int_equal(map.count, 1);

  // Delete
  mapRemove(&map, key);
  assert_int_equal(map.count, 1);

  // Test
  int value2 = 1000;
  bool new = mapPut(&map, key, strlen(key) + 1, &value2, sizeof(int));

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

  Map map;
  initMap(&map);

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

  Map map;
  initMap(&map);

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
    cmocka_unit_test(test_entry_free),
    cmocka_unit_test(test_entry_reassign),
    cmocka_unit_test(test_entry_reassign_same_key),
    cmocka_unit_test(test_map_get),
    cmocka_unit_test(test_map_clear),
    cmocka_unit_test(test_map_free),
    cmocka_unit_test(test_map_remove),
    cmocka_unit_test(test_map_remove_add_back),
    cmocka_unit_test(test_map_size),
    cmocka_unit_test(test_map_contains)};

const size_t mapTestsSize = sizeof(mapTests) / sizeof(mapTests[0]);
