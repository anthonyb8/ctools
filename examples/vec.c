#include <stdio.h>

#include "ctools/map.h"
#include "ctools/vec.h"

void intVecExample() {
  printf("\nInteger Example\n");

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
  int x = 5;
  vecPush(&vec, &x);

  // Set
  int y = 6;
  vecSet(&vec, 5, &y);

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
}

void strPtrVecExample() {
  printf("\nPointer Example\n");

  // New
  Vec vec = newVec(sizeof(char*));

  // Push
  const char* fruits[] = {"apple",       "banana", "coconut",
                          "dragonfruit", "berry",  "fig"};
  for (int i = 0; i < 6; i++) {
    vecPush(&vec, &fruits[i]);
  }

  // Length
  int length = vecLength(&vec);
  printf("Length is six: %d\n", length);

  // Get
  char** gotten = vecGet(&vec, 3);
  printf("Gotten value 'dragonfruit' : %s\n", *gotten);

  // Pop
  char* popped;
  int status = vecPop(&vec, &popped);
  printf("Popped value should be 'fig': %s\n", popped);
  printf("Length should be five: %d\n", vecLength(&vec));

  // Iter
  VecIterator iter = newVecIter(&vec);
  initVecIter(&vec, &iter);

  for (void* value = vecNext(&iter); value != NULL; value = vecNext(&iter)) {
    printf("Iteration: %s\n", *(char**)value);
    ;
  }

  freeVecIter(&iter);
  freeVec(&vec);
}

void strVecExample() {
  printf("\nString Example\n");
  // New
  Vec vec = newVec(sizeof(char[12]));

  // Push
  char* fruits[] = {"apple",       "banana", "coconut",
                    "dragonfruit", "berry",  "fig"};
  for (int i = 0; i < 6; i++) {
    vecPush(&vec, fruits[i]);
  }

  // Length
  int length = vecLength(&vec);
  printf("Length is six: %d\n", length);

  // Get
  char* gotten = vecGet(&vec, 4);
  printf("Gotten value 'berry' : %s\n", gotten);

  // Pop
  char popped[12];
  int status = vecPop(&vec, popped);
  printf("Popped value should be 'fig': %s\n", popped);
  printf("Length should be five: %d\n", vecLength(&vec));

  // Iter
  VecIterator iter = newVecIter(&vec);
  initVecIter(&vec, &iter);

  for (char* value = vecNext(&iter); value != NULL; value = vecNext(&iter)) {
    printf("Iteration: %s\n", value);
    ;
  }

  freeVecIter(&iter);
  freeVec(&vec);
}

int main() {
  intVecExample();
  strPtrVecExample();
  strVecExample();

  return 0;
}
