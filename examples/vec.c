#include <stdio.h>

#include "ctools/map.h"
#include "ctools/vec.h"

int main() {
  Vec vec_old;
  initVec(&vec_old, sizeof(int));

  int v = 10;
  vecPush(&vec_old, &v);
  printf("Should be ten: %d\n", *(int*)vecGet(&vec_old, 0));

  freeVec(&vec_old);

  // New
  Vec vec_n = newVec(sizeof(int));

  // Iter
  VecIterator iter = newVecIter(&vec_n);

  for (void* v = vecNext(&iter); v != NULL; v = vecNext(&iter)) {
    printf("Shouldnt be seeing this\n");
  }

  freeVecIter(&iter);
  freeVec(&vec_n);

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
  initVecIter(&vec, &iter);

  for (void* value = vecNext(&iter); value != NULL; value = vecNext(&iter)) {
    printf("Iteration: %d\n", *(int*)value);
  }
  freeVecIter(&iter);
  freeVec(&vec);

  return 0;
}
