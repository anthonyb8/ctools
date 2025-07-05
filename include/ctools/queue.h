#ifndef ctools_queue_h
#define ctools_queue_h

typedef struct {
  int capacity;
  int count;
  void* items;
} Queue;

void newQueue();
void initQueue();
void freeQueue();

// Current size
void size(Queue* queue);

// Append
void enqueue(Queue* queue);

// Get
void dequeue(Queue* queue);

// Check next item
void* peek(Queue* stack);

// Check if empty
void isEmpty(Queue* queue);
void size(Queue* queue);

#endif
