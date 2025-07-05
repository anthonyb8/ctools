#ifndef ctools_map_h
#define ctools_map_h

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <sys/wait.h>

#define MAX_LOAD 0.75
static char tombstone_marker;
#define TOMBSTONE ((void*)&tombstone_marker)

/**
 *  @brief Stores key as string and value as void* for generic behavior.
 */
typedef struct {
  char* key;
  void* value;
} Entry;

/**
 *  @brief Initialize entry.
 *
 *  @param key
 *  @param sizeKey
 *  @param value
 *  @param sizeVvalue
 *
 *  @return
 */
void initEntry(Entry* entry, char* key, size_t sizeKey, void* value,
               size_t sizeVvalue);

void reassignEntry(Entry* entry, char* key, size_t sizeKey, void* value,
                   size_t sizeValue);
/**
 *  @brief Free entry.
 *
 *  @param entry
 */
void freeEntry(Entry* entry);

/**
 *  @brief Dynamic Array the holds the values.
 */
typedef struct {
  int count;
  int capacity;
  Entry* entries;
} Map;

// Allocate
/**
 *  @brief Initalize map to default values.
 *
 *  @param map
 */
void initMap(Map* map);

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
bool mapPut(Map* map, char* key, size_t sizeKey, void* value, size_t sizeValue);

/**
 *  @brief Remove pair from map.
 *
 *  @param map
 *  @param key
 */
void mapRemove(Map* map, char* key);

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
void* mapGet(Map* map, char* key);

/**
 *  @brief Check if key is present in map.
 *
 *  @param map
 *  @param key
 *
 *  @return
 */
bool mapContains(Map* map, char* key);

/**
 *  @brief Number of entries in map currently.
 *
 *  @param map
 *
 *  @return
 */
int mapSize(Map* map);

// /**
//  *  @brief Return array or keys.
//  *
//  *  @param map
//  */
// void mapKeys(Map* map);
//
// /**
//  *  @brief Return array of values.
//  *
//  *  @param map
//  */
// void mapValues(Map* map);

/**
 *  @brief Pointer that tracks location, returns next live item.
 */
typedef struct {
  int capacity;
  Entry* next;
} MapIterator;

/**
 *  @brief Initalize map iterator object.
 *
 *  @param map
 *  @param iter
 */
void initMapIter(Map* map, MapIterator* iter);

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
bool mapNext(MapIterator* iter, Entry* value);

#endif
