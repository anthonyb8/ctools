#include <stdio.h>

#include "cvec/cvec.h"
#include "cvec/iterator.h"

int main() {
  Vec vec_old;
  vec_init(&vec_old, sizeof(int));

  int v = 10;
  vec_push(&vec_old, &v);
  printf("Should be ten: %d\n", *(int*)vec_peek(&vec_old));

  vec_init(&vec_old, sizeof(int));
  printf("Length is zero: %d\n", vec_len(&vec_old));

  // New
  Vec vec_n = vec_new(sizeof(int));

  // From
  int arr[] = {1, 2, 3, 4, 5};
  Vec vec = vec_from(&arr, sizeof(arr) / sizeof(int), sizeof(int));

  // Push
  int x = 6;
  vec_push(&vec, &x);

  // Length
  int length = vec_len(&vec);
  printf("Length is six: %d\n", length);

  // Get
  int* gotten = vec_get(&vec, 4);
  printf("Gotten value five: %d\n", *gotten);

  // Peek
  void* val = vec_peek(&vec);
  printf("Peek value should be six: %d\n", *(int*)val);

  // Pop
  int popped;
  int status = vec_pop(&vec, &popped);
  printf("Popped value should be six: %d\n", popped);
  printf("Length should be five: %d\n", vec_len(&vec));

  // Iter
  VecIterator iter = init_vec_iter(&vec);
  int value;
  while (next(&iter, &value)) {
    printf("Iteration: %d\n", value);
  }

  return 0;
}
