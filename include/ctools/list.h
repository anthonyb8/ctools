#ifndef ctools_list_h
#define ctools_list_h

#include <stdbool.h>
#include <stddef.h>

typedef struct Node Node;

// Nodes
struct Node {
  Node* next;
  void* value;
};

/**
 *  @brief Heap allocated node.
 *
 *  @param value
 *
 *  @return
 */
Node* initNode(void* value, size_t elem_size);

/**
 *  @brief Free node.
 *
 *  @param node
 */
void freeNode(Node* node);

// Singly Linked List
typedef struct {
  Node* head;
  Node* tail;
  int count;

  // function pointers
  bool (*cmp)(const void*, const void*);
  void (*print)(const void*);
} List;

/**
 *  @brief Initialze a List object. Typically use for stack allocated.
 *
 *  @param list
 *  @param cmp
 *  @param print
 */
void initList(List* list, bool (*cmp)(const void*, const void*),
              void (*print)(const void*));

/**
 *  @brief Create heap allocated list.
 *
 *  @param cmp
 *  @param print
 */
List* newList(bool (*cmp)(const void*, const void*),
              void (*print)(const void*));

/**
 *  @brief Free list.
 *
 *  @param list
 */
void freeList(List* list);

// Insert
/**
 *  @brief Insert at tail.
 *
 *  @param list
 *  @param value
 */
void listAppend(List* list, void* value, size_t elem_size);

/**
 *  @brief Insert at head
 *
 *  @param list
 *  @param value
 */
void listPrepend(List* list, void* value, size_t elem_size);

/**
 *  @brief Insert at given index.
 *
 *  @param list
 *  @param value
 */
void listInsert(List* list, int index, void* value, size_t elem_size);

// Get
/**
 *  @brief Get node at head.
 *
 *  @param list
 *
 *  @return
 */
Node* listHead(List* list);

/**
 *  @brief Get node at tail.
 *
 *  @param list
 *
 *  @return
 */
Node* listTail(List* list);

/**
 *  @brief Get node at given index
 *
 *  @param list
 *  @param index
 *
 *  @return
 */
Node* listAt(List* list, int index);

/**
 *  @brief Get first node with value given.
 *
 *  @param list
 *  @param value
 *
 *  @return
 */
Node* listFind(List* list, void* value);

// Update
/**
 *  @brief Set node at given index.
 *
 *  @param list
 *  @param value
 */
void listSet(List* list, int index, void* value, size_t elem_size);

// Delete
/**
 *  @brief Delete head node.
 *
 *  @param list
 *
 *  @return
 */
bool deleteHead(List* list);

/**
 *  @brief Delete tail node.
 *
 *  @param list
 *
 *  @return
 */
bool deleteTail(List* list);

/**
 *  @brief Delete first node with value.
 *
 *  @param list
 *  @param value
 *
 *  @return
 */
bool deleteValue(List* list, void* value);

// Other
/**
 *  @brief Print out link from head to tail.
 *
 *  @param list
 */
void printList(List* list);

/**
 *  @brief Check if list is empty.
 *
 *  @param list
 *  @return true if list is empty, false otherwise.
 */
bool listIsEmpty(List* list);

/**
 *  @brief Get index of first matching node.
 *
 *  @param list
 *  @param value
 *  @return index, or -1 if not found
 */
int listIndexOf(List* list, void* value);

/**
 *  @brief Remove and free all nodes, but keep list structure.
 *
 *  @param list
 */
void clearList(List* list);

/**
 *  @brief Get current size of the list.
 *
 *  @param list
 *  @return number of nodes
 */
int listSize(List* list);

#endif  // !ctools_list_h
