#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#include "ctools/list.h"

static inline Node* findNode(List* list, void* value) {
  Node* tmp = list->head;

  while (!list->cmp(tmp->value, value)) {
    if (tmp->next == NULL) {
      return NULL;
      ;
    }
    tmp = tmp->next;
  }
  return tmp;
}

static inline Node* findIndex(List* list, int index) {
  Node* tmp = list->head;
  int count = 0;

  while (count < index) {
    if (tmp->next == NULL) {
      return NULL;
    }
    tmp = tmp->next;
    count++;
  }
  return tmp;
}

// Nodes
Node* initNode(void* value, size_t elem_size) {
  Node* node = malloc(sizeof(Node));

  if (node == NULL) {
    printf("Error allocation memory for node.");
    exit(1);
  }

  node->value = malloc(elem_size);
  if (node->value == NULL) {
    exit(1);
  }
  memcpy(node->value, value, elem_size);

  node->next = NULL;
  return node;
}

void freeNode(Node* node) {
  free(node->value);
  node->next = NULL;
  node->value = NULL;
}

// Allocation
static inline void nullList(List* list, bool (*cmp)(const void*, const void*),
                            void (*print)(const void*)) {
  list->head = NULL;
  list->tail = NULL;
  list->count = 0;
  list->cmp = cmp;
  list->print = print;
}

void initList(List* list, bool (*cmp)(const void*, const void*),
              void (*print)(const void*)) {
  nullList(list, cmp, print);
}

List* newList(bool (*cmp)(const void*, const void*),
              void (*print)(const void*)) {
  List* list = malloc(sizeof(List));
  if (list == NULL) {
    exit(1);
  }
  nullList(list, cmp, print);
  return list;
}

void freeList(List* list) {
  clearList(list);
  list->head = NULL;
  list->tail = NULL;
  list->count = 0;
  list->cmp = NULL;
  list->print = NULL;
}

// Insert
void listPrepend(List* list, void* value, size_t elem_size) {
  Node* newNode = initNode(value, elem_size);
  if (list->count == 0) {
    list->head = newNode;
    list->tail = newNode;
  } else {
    newNode->next = list->head;
    list->head = newNode;
  }
  list->count++;
}

void listAppend(List* list, void* value, size_t elem_size) {
  Node* newNode = initNode(value, elem_size);
  if (list->count == 0) {
    list->head = newNode;
    list->tail = newNode;

  } else {
    list->tail->next = newNode;
    list->tail = newNode;
  }
  list->count++;
}

void listInsert(List* list, int index, void* value, size_t elem_size) {
  // Empty or index = 0 -> head
  if (list->head == NULL || index == 0) {
    return listPrepend(list, value, elem_size);
  } else if (index >= list->count) {
    return listAppend(list, value, elem_size);
  }

  Node* tmp = list->head;
  while (index > 1) {
    tmp = tmp->next;
    index--;
  }

  Node* newNode = initNode(value, elem_size);
  newNode->next = tmp->next;
  tmp->next = newNode;
  list->count++;
}

// Get
Node* listHead(List* list) { return list->head; }
Node* listTail(List* list) { return list->tail; }
Node* listAt(List* list, int index);

Node* listFind(List* list, void* value) {
  if (list->count == 0) {
    return NULL;
  }

  return findNode(list, value);
}

// Update
void listSet(List* list, int index, void* value, size_t elem_size) {
  if (list->head == NULL || index < 0 || index > list->count) {
    return;
  }

  Node* tmp = findIndex(list, index);
  if (tmp == NULL) return;

  free(tmp->value);
  tmp->value = malloc(elem_size);
  memcpy(tmp->value, value, elem_size);
}

// Delete
bool deleteHead(List* list) {
  if (list->count == 0) {
    return false;
  }

  Node* newHead = list->head->next;
  freeNode(list->head);
  list->head = newHead;

  list->count--;
  // printf("Count %d\n", list->count);
  return true;
}

bool deleteTail(List* list) {
  if (list->count == 0) {
    return false;
  }

  if (list->count == 1) return deleteHead(list);

  Node* tmp = list->head;
  Node* prev = NULL;

  while (tmp->next->next != NULL) {
    prev = tmp;
    tmp = tmp->next;
  }

  freeNode(tmp->next);
  tmp->next = NULL;
  list->tail = tmp;
  list->count--;

  return true;
}

bool deleteValue(List* list, void* value) {
  if (list->count == 0) {
    return false;
  }

  Node* tmp = list->head;
  Node* prev = NULL;

  while (tmp != NULL && !list->cmp(tmp->value, value)) {
    prev = tmp;
    tmp = tmp->next;
  }

  // Value not in list
  if (tmp == NULL) return false;

  if (prev == NULL) {
    deleteHead(list);
  } else if (tmp->next == NULL) {
    deleteTail(list);
  } else {
    prev->next = tmp->next;
    freeNode(tmp);
    list->count--;
  }

  return true;
}

// Other
void printList(List* list) {
  if (list->head == NULL) {
    printf("NULL\n");
    return;
  }
  Node* tmp = list->head;
  printf("[null] -> ");

  int count = 0;
  for (;;) {
    printf("Node: %d | value: ", count);
    list->print(tmp->value);
    printf(" -> ");
    if (tmp->next == NULL) {
      printf("%s\n", (char*)tmp->next);
      break;
    }
    tmp = tmp->next;
    count++;
  }
}

bool listIsEmpty(List* list) {
  if (list->head == NULL) {
    return true;
  }
  return false;
}

int listIndexOf(List* list, void* value) {
  if (list->count == 0) {
    return -1;
  }

  Node* tmp = list->head;
  int index = 0;

  while (!list->cmp(tmp->value, value)) {
    if (tmp->next == NULL) {
      return -1;
      ;
    }
    tmp = tmp->next;
    index++;
  }
  return index;
}

void clearList(List* list) {
  while (deleteHead(list)) {
    continue;
  }
  list->head = NULL;
  list->tail = NULL;
  list->count = 0;
}

int listSize(List* list) { return list->count; };
