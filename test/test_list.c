#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

// Third party
#include <cmocka.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ctools/comparators.h"
#include "ctools/list.h"

// Tests
static void test_list_append(void** state) {
  (void)state;

  List* list = newList(CMP_INT, PRINT_INT);

  // Test
  listAppend(list, &(int){100}, sizeof(int));

  // Validate
  Node* head = listHead(list);
  Node* tail = listTail(list);
  assert_int_equal(*(int*)head->value, *(int*)tail->value);
  assert_int_equal(*(int*)head->value, 100);
  assert_int_equal(listSize(list), 1);
}

static void test_list_prepend(void** state) {
  (void)state;

  List* list = newList(CMP_INT, PRINT_INT);

  // Test
  listPrepend(list, &(int){100}, sizeof(int));

  // Validate
  Node* head = listHead(list);
  Node* tail = listTail(list);
  assert_int_equal(*(int*)head->value, *(int*)tail->value);
  assert_int_equal(*(int*)head->value, 100);
  assert_int_equal(listSize(list), 1);
}

static void test_list_insert(void** state) {
  (void)state;

  List* list = newList(CMP_INT, PRINT_INT);
  listAppend(list, &(int){100}, sizeof(int));
  listAppend(list, &(int){100}, sizeof(int));

  // Test
  listInsert(list, 1, &(int){101}, sizeof(int));
  Node* node = listHead(list);

  // Validate
  // shoudl be second from head
  assert_int_equal(*(int*)node->next->value, 101);
  assert_int_equal(listSize(list), 3);
}

static void test_list_at(void** state) {
  (void)state;

  List* list = newList(CMP_INT, PRINT_INT);
  listPrepend(list, &(int){200}, sizeof(int));
  listPrepend(list, &(int){100}, sizeof(int));
  listPrepend(list, &(int){100}, sizeof(int));

  // Test
  Node* node = listFind(list, &(int){200});

  // Validate
  assert_ptr_equal(node->next, NULL);  // tail
}

static void test_list_at_multiple(void** state) {
  (void)state;

  List* list = newList(CMP_INT, PRINT_INT);
  listAppend(list, &(int){100}, sizeof(int));
  listAppend(list, &(int){100}, sizeof(int));

  // Test
  Node* node = listFind(list, &(int){100});

  // Validate
  Node* head = listHead(list);
  assert_int_equal(node->next, head->next);
  assert_int_equal(*(int*)node->value, 100);
}

static void test_delete_head(void** state) {
  (void)state;

  List* list = newList(CMP_INT, PRINT_INT);
  listAppend(list, &(int){100}, sizeof(int));
  listAppend(list, &(int){200}, sizeof(int));

  // Test
  assert_int_equal(listSize(list), 2);
  deleteHead(list);

  // Validate
  Node* head = listHead(list);
  assert_ptr_equal(head->next, NULL);
  assert_int_equal(*(int*)head->value, 200);
  assert_int_equal(listSize(list), 1);
}

static void test_delete_tail(void** state) {
  (void)state;

  List* list = newList(CMP_INT, PRINT_INT);
  listAppend(list, &(int){100}, sizeof(int));
  listAppend(list, &(int){500}, sizeof(int));

  // Test
  assert_int_equal(listSize(list), 2);
  deleteTail(list);

  // Validate
  Node* tail = listTail(list);
  assert_int_equal(tail->next, NULL);
  assert_int_equal(*(int*)tail->value, 100);
  assert_int_equal(listSize(list), 1);
}

static void test_delete_value(void** state) {
  (void)state;

  List* list = newList(CMP_INT, PRINT_INT);
  listAppend(list, &(int){100}, sizeof(int));
  listAppend(list, &(int){500}, sizeof(int));
  listAppend(list, &(int){100}, sizeof(int));

  // Test
  deleteValue(list, &(int){500});

  // Validate
  Node* head = listHead(list);
  Node* tail = listTail(list);
  assert_ptr_equal(head->next, tail);
}

static void test_list_not_empty(void** state) {
  (void)state;

  List* list = newList(CMP_INT, PRINT_INT);
  listAppend(list, &(int){100}, sizeof(int));
  listAppend(list, &(int){100}, sizeof(int));

  // Test
  assert_false(listIsEmpty(list));
}

static void test_list_is_empty(void** state) {
  (void)state;

  List* list = newList(CMP_INT, PRINT_INT);

  // Test
  assert_true(listIsEmpty(list));
}

static void test_list_size(void** state) {
  (void)state;
  List* list = newList(CMP_INT, PRINT_INT);
  listAppend(list, &(int){100}, sizeof(int));
  listAppend(list, &(int){100}, sizeof(int));

  // Test
  assert_int_equal(2, listSize(list));
}

static void test_list_clear(void** state) {
  (void)state;
  List* list = newList(CMP_INT, PRINT_INT);
  listAppend(list, &(int){100}, sizeof(int));
  listAppend(list, &(int){100}, sizeof(int));
  assert_int_equal(2, listSize(list));

  // Test
  clearList(list);

  // Validate
  assert_int_equal(0, listSize(list));
}

static void test_list_set(void** state) {
  (void)state;

  List* list = newList(CMP_INT, PRINT_INT);
  listAppend(list, &(int){100}, sizeof(int));
  listAppend(list, &(int){100}, sizeof(int));
  listAppend(list, &(int){100}, sizeof(int));
  assert_int_equal(3, listSize(list));

  // Test
  listSet(list, 1, &(int){500}, sizeof(int));

  // Validate
  Node* head = listHead(list);
  assert_int_equal(*(int*)head->next->value, 500);
  assert_int_equal(3, listSize(list));
}

static void test_list_index_of(void** state) {
  (void)state;

  List* list = newList(CMP_INT, PRINT_INT);
  listAppend(list, &(int){100}, sizeof(int));
  listAppend(list, &(int){200}, sizeof(int));
  listAppend(list, &(int){300}, sizeof(int));
  assert_int_equal(3, listSize(list));

  // Test
  assert_int_equal(listIndexOf(list, &(int){100}), 0);
  assert_int_equal(listIndexOf(list, &(int){200}), 1);
  assert_int_equal(listIndexOf(list, &(int){300}), 2);
}

const struct CMUnitTest listTests[] = {cmocka_unit_test(test_list_append),
                                       cmocka_unit_test(test_list_prepend),
                                       cmocka_unit_test(test_list_insert),
                                       cmocka_unit_test(test_list_at),
                                       cmocka_unit_test(test_list_at_multiple),
                                       cmocka_unit_test(test_list_set),
                                       cmocka_unit_test(test_delete_head),
                                       cmocka_unit_test(test_delete_tail),
                                       cmocka_unit_test(test_delete_value),
                                       cmocka_unit_test(test_list_is_empty),
                                       cmocka_unit_test(test_list_not_empty),
                                       cmocka_unit_test(test_list_index_of),
                                       cmocka_unit_test(test_list_clear),
                                       cmocka_unit_test(test_list_size)};

const size_t listTestsSize = sizeof(listTests) / sizeof(listTests[0]);
