#ifndef ctools_map_h
#define ctools_map_h

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <sys/wait.h>

#include "ctools/comparators.h"

#define MAX_LOAD 0.75

/**
 *  @brief Dynamic Array the holds the values.
 */
typedef struct {
  void* entries;
  size_t key_size;
  size_t value_size;
  int count;
  int capacity;
  bool (*cmp)(const void*, const void*);
} Map;

// Allocate
/**
 *  @brief Initalize map to default values.
 *
 *  @param map
 */
void initMap(Map* map, size_t key_size, size_t value_size,
             bool (*cmp)(const void*, const void*));

/**
 *  @brief Creates new map and returns object.
 *
 *  @return
 */
Map newMap(size_t key_size, size_t value_size,
           bool (*cmp)(const void*, const void*));

/**
 *  @brief Free Map.
 *
 *  @param map
 */
void freeMap(Map* map);

// Edit
/**
 *  @brief Update if exists, else insert.
 *
 *  @param map
 *  @param key
 *  @param value
 */
bool mapPut(Map* map, void* key, void* value);

/**
 *  @brief Remove pair from map.
 *
 *  @param map
 *  @param key
 */
void mapRemove(Map* map, void* key);

/**
 *  @brief Clean entire map(use with caution).
 *
 *  @param map
 */
void mapClear(Map* map);

// Values
/**
 *  @brief Get value in map.
 *
 *  @param map
 *  @param key
 *
 *  @return
 */
void* mapGet(Map* map, void* key);

/**
 *  @brief Check if key is present in map.
 *
 *  @param map
 *  @param key
 *
 *  @return
 */
bool mapContains(Map* map, void* key);

/**
 *  @brief Number of entries in map currently.
 *
 *  @param map
 *
 *  @return
 */
int mapSize(Map* map);

/**
 *  @brief Pointer that tracks location, returns next live item.
 */
typedef struct {
  void* next;
  int remaining;
  Map* map;
  // size_t key_size;
  // size_t value_size;
} MapIterator;

/**
 *  @brief Initalize map iterator object.
 *
 *  @param map
 *  @param iter
 */
void initMapIter(Map* map, MapIterator* iter);

/**
 *  @brief Create new MapIterator.
 *
 *  @param map
 *
 *  @return
 */
MapIterator newMapIter(Map* map);

/**
 *  @brief Free mapiterator.
 *
 *  @param iter
 */
void freeMapIter(MapIterator* iter);

/**
 *  @brief Get next value, return bool indicating remainng items.
 *
 *  @param iter
 *  @param value
 *
 *  @return
 */
void* mapNext(MapIterator* iter);

#endif
