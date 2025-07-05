#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ctools/map.h"

void fillMap(Map* map, int count) {
  for (int i = 0; i < count; i++) {
    char kbuf[2] = {'a' + i, '\0'};
    char* key = strdup(kbuf);

    int* value = malloc(sizeof(int));
    *value = i;

    mapPut(map, key, strlen(key), value, sizeof(int));
  }
}

int main() {
  Map map;
  initMap(&map);

  // seed
  int length = 8;
  fillMap(&map, length);

  // Get
  int* a = mapGet(&map, "a");
  printf("Value: %d\n", *a);

  int* b = mapGet(&map, "b");
  printf("Value: %d\n", *b);

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
  printf("Value: %s\n", (char*)e);  // Should be random

  // Contains
  bool check = mapContains(&map, "a");
  printf("Check: %d\n", check);  // 1 = True

  // Clear
  mapClear(&map);
  printf("Length: %d\n", mapSize(&map));

  // Cleanup
  freeMap(&map);

  return 0;
}
