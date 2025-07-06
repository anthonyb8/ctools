#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ctools/map.h"

void fillMapStrInt(Map* map, int count) {
  for (int i = 0; i < count; i++) {
    char kbuf[2] = {'a' + i, '\0'};
    char* key = strdup(kbuf);

    int* value = malloc(sizeof(int));
    *value = i;

    mapPut(map, key, value);
  }
}

void fillMapIntStr(Map* map, int count) {
  for (int i = 0; i < count; i++) {
    int* key = malloc(sizeof(int));
    *key = i;

    char vbuf[2] = {'a' + i, '\0'};
    char* value = strdup(vbuf);

    mapPut(map, key, value);
  }
}

int main() {
  Map map = newMap(2, sizeof(int), CMP_STR);

  // seed
  int length = 8;
  fillMapStrInt(&map, length);

  // Get
  void* a = mapGet(&map, "a");
  printf("Value: %d\n", *(int*)a);

  void* b = mapGet(&map, "b");
  printf("Value: %d\n", *(int*)b);

  int* c = mapGet(&map, "c");
  printf("Value: %d\n", *c);

  int* d = mapGet(&map, "d");
  printf("Value: %d\n", *d);

  int* e = mapGet(&map, "e");
  printf("Value: %d\n", *e);

  int* f = mapGet(&map, "f");
  printf("Value: %d\n", *f);

  int* g = mapGet(&map, "g");
  printf("Value: %d\n", *g);

  int* h = mapGet(&map, "h");
  printf("Value: %d\n", *h);

  // Size
  printf("Length %d\n", mapSize(&map));

  // Remove
  mapRemove(&map, "e");
  int* eNull = mapGet(&map, "e");
  printf("Value: %s\n", (char*)e);  // Should be undefined

  // Contains
  bool check = mapContains(&map, "a");
  printf("Check: %d\n", check);  // 1 = True

  // Iterate
  MapIterator iter;
  initMapIter(&map, &iter);

  // Entry value;
  for (void* entry = mapNext(&iter); entry != NULL; entry = mapNext(&iter)) {
    printf("Key: %s Value : %d\n", (char*)entry, *(int*)(entry + 2));
  }

  freeMapIter(&iter);

  // Clear
  mapClear(&map);
  printf("Length: %d\n", mapSize(&map));  // Should be 0

  // Iterate
  int count;

  for (Entry* entry = mapNext(&iter); entry != NULL;
       entry = mapNext(&iter), count++) {
    printf("Key: %s Value : %d\n", (char*)entry,
           *(int*)(entry + 2));  /// Shouldnt print
  }
  printf("Count : %d\n", count);  // Should be 0

  freeMapIter(&iter);

  // Cleanup
  freeMap(&map);

  // Differnt  type
  initMap(&map, sizeof(int), 2, CMP_INT);

  // seed
  fillMapIntStr(&map, length);

  // Get
  void* zero = mapGet(&map, &(int){0});  // Edge case ZERO not a valid key
  printf("Value: %s\n", (char*)zero);

  void* one = mapGet(&map, &(int){1});
  printf("Value: %s\n", (char*)one);

  void* two = mapGet(&map, &(int){2});
  printf("Value: %s\n", (char*)two);

  void* three = mapGet(&map, &(int){3});
  printf("Value: %s\n", (char*)three);

  void* four = mapGet(&map, &(int){4});
  printf("Value: %s\n", (char*)four);

  void* five = mapGet(&map, &(int){5});
  printf("Value: %s\n", (char*)five);

  void* six = mapGet(&map, &(int){6});
  printf("Value: %s\n", (char*)six);

  void* seven = mapGet(&map, &(int){7});
  printf("Value: %s\n", (char*)seven);

  // Remove
  mapRemove(&map, &(int){7});
  int* removedNull = mapGet(&map, &(int){7});
  printf("Undefined Value: %s\n", (char*)removedNull);  // Should be undefined

  // Contains
  bool checkInt = mapContains(&map, &(int){1});
  printf("Check: %d\n", checkInt);  // 1 = True

  // Cleanup
  freeMap(&map);

  return 0;
}
