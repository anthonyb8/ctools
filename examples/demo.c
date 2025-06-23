#include <stdio.h>

#include "cvec/cvec.h"

int main() {
  int arr[] = {1, 2, 3, 4, 5};

  // New
  Vec vec_n = vec_new(sizeof(int));
  printf("Length new: %d\n", vec_len(&vec_n));

  //
  printf("Length from: %d\n", vec_len(&vec_n));
  int v = 1;
  vec_push(&vec_n, &v);
  printf("Length from: %d\n", vec_len(&vec_n));

  // From
  Vec vec = vec_from(&arr, sizeof(arr) / sizeof(int), sizeof(int));
  printf("Length from: %d\n", vec_len(&vec));

  // Push
  int x = 6;
  vec_push(&vec, &x);

  // Length
  int length = vec_len(&vec);
  printf("Length is six: %d\n", length);

  // Get
  int* gotten = vec_get(&vec, 5);
  printf("Gotten value: %d\n", *gotten);

  // Peek
  void* val = vec_peek(&vec);
  printf("Value should be six: %d\n", *(int*)val);

  // Pop
  int popped;
  int status = vec_pop(&vec, &popped);
  printf("Status code %d\n", status);
  printf("Value should be six: %d\n", popped);
  printf("Length from: %d\n", vec_len(&vec));

  // Iter
  VecIterator iter = init_vec_iter(&vec);
  int value;
  while (next(&iter, &value)) {
    printf("Iteration: %d\n", value);
  }
  printf("\n");

  // Push
  int len = vec_len(&vec);
  printf("Length is six: %d\n", len);
  int y = 8;
  vec_push(&vec, &y);
  vec_push(&vec, &y);
  vec_push(&vec, &y);
  vec_push(&vec, &y);
  vec_push(&vec, &y);
  vec_push(&vec, &y);
  printf("Length from: %d\n", vec_len(&vec));

  // Iter
  VecIterator iter2 = init_vec_iter(&vec);
  while (next(&iter2, &value)) {
    printf("Iteration: %d\n", value);
  }

  return 0;
}

// int main() {
//   int arr[5] = {1, 2, 3, 4, 5};
//   void* ptr = arr;
//   int* ptr2 = arr;
//
//   printf("Index : %d\n", arr[0]);
//   printf("Ptr: %d\n", *(int*)ptr);
//   printf("Ptr2: %d\n", *ptr2);
//
//   char* char_ptr = (char*)ptr;
//
//   printf("index 2:  %d\n",
//          *(int*)(char_ptr + 2 * sizeof(int)));  // prints arr[2]
//   ptr2 += 2;
//   printf("Index 2: %d\n", *ptr2);
//
//   return 0;
//
