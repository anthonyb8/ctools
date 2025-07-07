#include <stdio.h>

#include "ctools/comparators.h"
#include "ctools/list.h"

void listIntExample() {
  List* list = newList(CMP_INT, PRINT_INT);

  // Append
  listPrepend(list, &(int){100}, sizeof(int));
  int index100 = listIndexOf(list, &(int){100});
  printf("Index zero: %d\n", index100);

  // Insert
  listInsert(list, 1, &(int){200}, sizeof(int));
  int index200 = listIndexOf(list, &(int){200});
  printf("Index one: %d\n", index200);

  // Prepend
  listAppend(list, &(int){300}, sizeof(int));
  int index300 = listIndexOf(list, &(int){300});
  printf("Index two: %d\n", index300);

  // Set
  listSet(list, 1, &(int){500}, sizeof(int));
  int index500 = listIndexOf(list, &(int){500});
  printf("Index one: %d\n", index500);

  // Find
  Node* node = listFind(list, &(int){200});
  printf("Should be null: %s\n", (char*)node);

  Node* node1 = listFind(list, &(int){500});
  printf("Should be 500: %d\n", *(int*)node1->value);

  Node* head = listHead(list);
  printf("Should be 100: %d\n", *(int*)head->value);

  Node* tail = listTail(list);
  printf("Should be 300: %d\n", *(int*)tail->value);

  // Size
  printf("Size three : %d\n", listSize(list));

  // Delete
  deleteHead(list);
  deleteTail(list);
  deleteValue(list, &(int){500});
  printList(list);

  // Size
  printf("Size zero : %d\n", listSize(list));
  printf("Empty true: %d\n", listIsEmpty(list));
}

int main() {
  listIntExample();
  return 0;
}
