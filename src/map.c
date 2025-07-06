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
static inline uint32_t hashString(void *key, int length) {
  uint8_t *bytes = (uint8_t *)key;
  uint32_t hash = 2166136261u;

  for (int i = 0; i < length; i++) {
    hash ^= bytes[i];
    hash *= 16777619;
  }
  return hash;
}

static inline bool isNull(uint8_t *bytes, size_t size) {
  for (size_t i = 0; i < size; i++) {
    if (bytes[i] != 0) return false;
  }
  return true;
}

// Constant & implmentation found at
static uint8_t *linearProbing(Map *map, void *entries, void *key,
                              size_t entrySize, size_t capacity) {
  uint32_t hash = hashString(key, map->key_size);
  uint32_t index = hash % capacity;
  uint8_t *tombstone = NULL;

  // iterates until found matching key or hit an open slot, if hit an open slot
  // after seeing  a tombstone return tombstone, else return the open slot
  for (;;) {
    uint8_t *entry = entries + (index * entrySize);
    void *value = entry + map->key_size;

    if (isNull(entry, map->key_size)) {
      if (isNull(value, map->value_size)) {
        return tombstone != NULL ? tombstone : entry;
      } else {
        if (tombstone == NULL) {
          tombstone = entry;
        }
      }
    } else if (map->cmp(entry, key)) {
      return entry;
    }

    // Wraps back to 0 when end hit
    index = (index + 1) % map->capacity;
  }
}

// Allocates a new array with new capacity and itializes to nulls
// Then reinserts old entries based on the new length
static void adjustArray(Map *map) {
  int newCapacity = grow_capacity(map->capacity);
  size_t entrySize = map->key_size + map->value_size;

  uint8_t *oldEntries = (uint8_t *)map->entries;
  uint8_t *newEntries = malloc(newCapacity * entrySize);

  // Zero out new buffer
  memset(newEntries, 0, newCapacity * entrySize);
  map->count = 0;

  // Iterate over existing entries
  for (int i = 0; i < map->capacity; i++) {
    uint8_t *oldEntry = oldEntries + (i * entrySize);
    void *key = oldEntry;
    void *value = oldEntry + map->key_size;

    if (isNull(key, map->key_size)) continue;

    uint8_t *dest = linearProbing(map, newEntries, key, entrySize, newCapacity);

    memcpy(dest, key, map->key_size);
    memcpy(dest + map->key_size, value, map->value_size);
    map->count++;
  }

  free(map->entries);
  map->entries = newEntries;
  map->capacity = newCapacity;
}

// Allocate
Map newMap(size_t key_size, size_t value_size,
           bool (*cmp)(const void *, const void *)) {
  return (Map){
      .count = 0,
      .capacity = 0,
      .entries = NULL,
      .key_size = key_size,
      .value_size = value_size,
      .cmp = cmp,
  };
}

void initMap(Map *map, size_t key_size, size_t value_size,
             bool (*cmp)(const void *, const void *)) {
  map->count = 0;
  map->capacity = 0;
  map->entries = NULL;
  map->key_size = key_size;
  map->value_size = value_size;
  map->cmp = cmp;
}

void freeMap(Map *map) {
  free(map->entries);
  map->count = 0;
  map->capacity = 0;
  map->entries = NULL;
  map->key_size = 0;
  map->value_size = 0;
}

// Edit
bool mapPut(Map *map, void *key, void *value) {
  if (map->count >= map->capacity * MAX_LOAD) {
    adjustArray(map);
  }

  uint8_t *entry = linearProbing(
      map, map->entries, key, (map->key_size + map->value_size), map->capacity);

  bool isNewKey = isNull(entry, map->key_size);
  if (isNewKey && isNull(entry + map->key_size, map->value_size)) {
    map->count++;
  }

  memcpy(entry, key, map->key_size);
  memcpy(entry + map->key_size, value, map->value_size);

  return isNewKey;
}

void mapRemove(Map *map, void *key) {
  if (map->count == 0) return;

  // Get destination in new array
  uint8_t *entry = linearProbing(
      map, map->entries, key, (map->key_size + map->value_size), map->capacity);

  memset(entry, 0, map->key_size);
  // TOMBSTONE IS 1
  memset(entry + map->key_size, 0, map->value_size);
  memset(entry + map->key_size + map->value_size - 1, 1, 1);
}

void mapClear(Map *map) {
  size_t entrySize = map->key_size + map->value_size;
  memset(map->entries, 0, map->capacity * entrySize);
  map->count = 0;
}

// Values
void *mapGet(Map *map, void *key) {
  if (map->capacity == 0) return NULL;

  // Get destination in new array
  uint8_t *entry = linearProbing(
      map, map->entries, key, (map->key_size + map->value_size), map->capacity);
  if (isNull(entry, map->key_size)) return NULL;
  return entry + map->key_size;
}

int mapSize(Map *map) { return map->count; }

bool mapContains(Map *map, void *key) {
  if (map->capacity == 0) return false;

  // Get destination in new array
  uint8_t *entry = linearProbing(
      map, map->entries, key, (map->key_size + map->value_size), map->capacity);

  if (isNull(entry, map->key_size)) return NULL;

  return true;
}

// Iterator
void initMapIter(Map *map, MapIterator *iter) {
  iter->remaining = map->capacity;
  iter->next = map->entries;
  iter->map = map;
}

MapIterator newMapIter(Map *map) {
  return (MapIterator){
      .remaining = map->capacity,
      .next = map->entries,
      .map = map,
  };
}

void freeMapIter(MapIterator *iter) {
  iter->remaining = 0;
  iter->next = NULL;
  iter->map = NULL;
}

void *mapNext(MapIterator *iter) {
  while (iter->remaining > 0) {
    void *current = iter->next;
    iter->next += (iter->map->key_size + iter->map->value_size);
    iter->remaining--;

    if (!isNull(current, iter->map->key_size)) {
      return current;
    }
  }

  return NULL;
}
