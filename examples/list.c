#include <stdio.h>
#include <stdlib.h>

#include "ctools/list.h"

CMP_FUNCTION(int)
PRINT_FUNCTION(int, "%d")

int main() {
  // Node node;
  // Node* node = initNode("testing",);
  // freeNode(node);

  // List
  List listStack;
  initList(&listStack, int_cmp, int_print);

  List* listHeap = newList(int_cmp, int_print);

  // Append
  for (int i = 0; i < 10; i++) {
    int* value = malloc(sizeof(int));
    *value = i;
    listAppend(listHeap, value, sizeof(int));
  }

  // Prepend
  for (int i = 10; i < 20; i++) {
    int* value = malloc(sizeof(int));
    *value = i;
    listPrepend(listHeap, value, sizeof(int));
  }

  // Insert
  int g = 99;
  listInsert(listHeap, 9, &g, sizeof(int));

  // Get
  int* d = (int*)listHead(listHeap)->value;
  printf("Head : %d\n", *d);

  int* e = (int*)listTail(listHeap)->value;
  printf("Tail : %d\n", *e);

  int p = 8;
  Node* found_node = listFind(listHeap, &p);
  printf("Value : %d | Next Value: %d\n", *(int*)found_node->value,
         *(int*)found_node->next->value);

  // Update
  int y = 1000;
  listSet(listHeap, 0, &y);

  // Delete
  deleteHead(listHeap);
  deleteTail(listHeap);

  // deleteValue(listHeap, node->next->value);

  // Other
  printList(listHeap);

  bool empty = listIsEmpty(listHeap);
  printf("isEmpty %b\n", empty);

  int z = 99;
  int index = listIndexOf(listHeap, &z);
  printf("indexOf %d\n", index);

  int size = listSize(listHeap);
  printf("size %d\n", size);

  clearList(listHeap);

  int size2 = listSize(listHeap);
  printf("size %d\n", size2);

  return 0;
}
