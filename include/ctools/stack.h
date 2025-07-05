#ifndef ctools_stack_h
#define ctools_stack_h

#include <stdbool.h>
#define STACK_MAX 256

typedef struct {
  void* top;
  void* stack[STACK_MAX];
} Stack;

void newStack();
void initStack();
void freeStack();

// Add
void push(Stack* stack, void* value);

// Remove
void* pop(Stack* stack);

// Check next item
void* peek(Stack* stack);
bool isFull(Stack* stack);
bool isEmpty(Stack* stack);
bool size(Stack* stack);

#endif  // !ctools_queue_h
