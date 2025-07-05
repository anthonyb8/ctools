#include <stdio.h>

#include "ctools/vec.h"

int main() {
  Vec vec_old;
  initVec(&vec_old, sizeof(int));

  int v = 10;
  vecPush(&vec_old, &v);
  // printf("Should be ten: %d\n", *(int*)vecPeek(&vec_old));

  initVec(&vec_old, sizeof(int));
  printf("Length is zero: %d\n", vecLength(&vec_old));

  // New
  Vec* vec_n = newVec(sizeof(int));

  // From
  int array[] = {1, 2, 3, 4, 5};
  Vec vec = fromArray(&array, sizeof(array) / sizeof(int), sizeof(int));

  // Push
  int x = 6;
  vecPush(&vec, &x);

  // Length
  int length = vecLength(&vec);
  printf("Length is six: %d\n", length);

  // Get
  int* gotten = vecGet(&vec, 4);
  printf("Gotten value five: %d\n", *gotten);

  // Pop
  int popped;
  int status = vecPop(&vec, &popped);
  printf("Popped value should be six: %d\n", popped);
  printf("Length should be five: %d\n", vecLength(&vec));

  // Iter
  VecIterator iter = initVecIter(&vec);
  int value;
  while (vecNext(&iter, &value)) {
    printf("Iteration: %d\n", value);
  }

  return 0;
}
