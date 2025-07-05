#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#include "ctools/map.h"
#include "memory.h"

// Constant & implmentation found at
// https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function
static inline uint32_t hashString(const char *key, int length) {
  uint32_t hash = 2166136261u;
  for (int i = 0; i < length; i++) {
    hash ^= (uint8_t)*key;
    hash *= 16777619;
  }
  return hash;
}

// Constant & implmentation found at
static Entry *linearProbing(Entry *entries, const char *key, int capacity) {
  uint32_t hash = hashString(key, capacity);
  uint32_t index = hash % capacity;
  Entry *tombstone = NULL;

  // iterates until found matching key or hit an open slot, if hit an open slot
  // after seeing  a tombstone return tombstone, else return the open slot
  for (;;) {
    Entry *entry = &entries[index];
    if (entry->key == NULL) {
      if (entry->value == NULL) {
        return tombstone != NULL ? tombstone : entry;
      } else {
        if (tombstone == NULL) {
          tombstone = entry;
        }
      }
    } else if (strcmp(entry->key, key) == 0) {
      return entry;
    }

    // Wraps back to 0 when end hit
    index = (index + 1) % capacity;
  }
}

// Allocates a new array with new capacity and itializes to nulls
// Then reinserts old entries based on the new length
static void adjustArray(Map *map) {
  int newCapacity = grow_capacity(map->capacity);
  Entry *oldEntries = map->entries;
  Entry *newEntries = malloc(newCapacity * sizeof(Entry));

  // Set all the value to null in line with old length
  for (int i = 0; i < newCapacity; i++) {
    newEntries[i].key = NULL;
    newEntries[i].value = NULL;
  }

  map->count = 0;

  // Iterate over existing entries
  for (int i = 0; i < map->capacity; i++) {
    Entry *entry = &oldEntries[i];
    if (entry->key == NULL) continue;  // Null entry no need to copy

    // Get destination in new array
    Entry *dest = linearProbing(newEntries, entry->key, newCapacity);

    // Update new entry with old entry
    dest->key = entry->key;
    dest->value = entry->value;
    map->count++;
  }

  // Free old array
  FREE_ARRAY(Entry, map->entries);

  // Assign new array
  map->entries = newEntries;
  map->capacity = newCapacity;
}

// Entry
void reassignEntry(Entry *entry, char *key, size_t sizeKey, void *value,
                   size_t sizeValue) {
  if (entry->key == NULL || strcmp(key, entry->key) != 0) {
    free(entry->key);

    entry->key = malloc(sizeKey);
    if (entry->key == NULL) {
      exit(1);
    }
    memcpy(entry->key, key, sizeKey);
  }

  if (entry->value != NULL && entry->value != TOMBSTONE) {
    free(entry->value);
  }

  entry->value = malloc(sizeValue);
  if (entry->value == NULL) {
    free(entry->key);
    exit(1);
  }
  memcpy(entry->value, value, sizeValue);
}

void initEntry(Entry *entry, char *key, size_t sizeKey, void *value,
               size_t sizeValue) {
  entry->key = malloc(sizeKey);
  if (entry->key == NULL) {
    exit(1);
  }
  memcpy(entry->key, key, sizeKey);

  entry->value = malloc(sizeValue);
  if (entry->value == NULL) {
    free(entry->key);
    exit(1);
  }
  memcpy(entry->value, value, sizeValue);
}

void tombstoneEntry(Entry *entry) {
  if (!entry) return;

  free(entry->key);
  entry->key = NULL;

  free(entry->value);
  entry->value = TOMBSTONE;
}

void freeEntry(Entry *entry) {
  if (!entry) return;

  free(entry->key);
  entry->key = NULL;

  free(entry->value);
  entry->value = NULL;
}

// Allocate
void initMap(Map *map) {
  map->count = 0;
  map->capacity = 0;
  map->entries = NULL;
}

void freeMap(Map *map) {
  mapClear(map);                    // releases any entry memeory
  FREE_ARRAY(Entry, map->entries);  // releases array memory
  initMap(map);
}

// Edit
bool mapPut(Map *map, char *key, size_t sizeKey, void *value,
            size_t sizeValue) {
  if (map->count >= map->capacity * MAX_LOAD) {
    adjustArray(map);
  }
  Entry *entry = linearProbing(map->entries, key, map->capacity);

  bool isNewKey = entry->key == NULL;
  if (isNewKey && entry->value == NULL) {
    map->count++;
  }

  reassignEntry(entry, key, sizeKey, value, sizeValue);

  return isNewKey;
}

void mapRemove(Map *map, char *key) {
  if (map->count == 0) return;

  // Get destination in new array
  Entry *entry = linearProbing(map->entries, key, map->capacity);
  tombstoneEntry(entry);
}

void mapClear(Map *map) {
  for (int i = 0; i < map->capacity; i++) {
    Entry *entry = map->entries + i;
    if (entry->key != NULL) {
      freeEntry(entry);
    }
  }
  map->count = 0;
}

// Values
void *mapGet(Map *map, char *key) {
  if (map->capacity == 0) return NULL;

  // Get destination in new array
  Entry *entry = linearProbing(map->entries, key, map->capacity);

  if (entry->key == NULL) return NULL;

  return entry->value;
}

int mapSize(Map *map) { return map->count; }

bool mapContains(Map *map, char *key) {
  if (map->capacity == 0) return false;

  // Get destination in new array
  Entry *entry = linearProbing(map->entries, key, map->capacity);

  if (entry->key == NULL) return false;

  return true;
}

// Iterator
void initMapIter(Map *map, MapIterator *iter) {
  iter->capacity = map->capacity;
  iter->next = &map->entries[0];
}

void freeMapIter(MapIterator *iter) {
  iter->capacity = 0;
  iter->next = NULL;
}

bool mapNext(MapIterator *iter, Entry *value) {
  printf("Capacity %d\n", iter->capacity);

  for (;;) {
    if (iter->next->key == NULL) {
      iter->next++;
      continue;
    } else {
      value = iter->next->value;
      break;
    }
  }
  iter->next++;
  return true;
}
