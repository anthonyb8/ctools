#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ctools/openmap.h"
#include "memory.h"

#define TABLE_MAX_LOAD 0.75

// uint32_t hashString(const char* key, int length);

static Entry* findEntry(Entry* entries, int capacity, char* key) {
  uint32_t hash = hashString(key, strlen(key));
  uint32_t index = hash % capacity;
  Entry* tombstone = NULL;

  for (;;) {
    Entry* entry = &entries[index];
    if (entry->key == NULL) {
      if (entry->value == NULL) {
        // Empty entry.
        return tombstone != NULL ? tombstone : entry;
      } else {
        // We found a tombstone.
        if (tombstone == NULL) tombstone = entry;
      }
    } else if (entry->key == key) {
      // We found the key.
      return entry;
    }

    index = (index + 1) % capacity;
  }
}

Entry* allocateNewArray(Table* table, int capacity) {
  Entry* entries = reallocate(table->entries, capacity);

  for (int i = 0; i < table->capacity; i++) {
    table->entries++;
    printf("Table enties\n");
  }

  for (int i = 0; i < capacity; i++) {
    entries++;
    printf("New entries\n");
  }

  for (int i = 0; i < capacity; i++) {
    entries[i].key = NULL;
    entries[i].value = NULL;
  }
  return entries;
}

void adjustCapacity(Table* table, int capacity) {
  Entry* entries = allocateNewArray(table, capacity);  //, int capacity)

  table->count = 0;

  for (int i = 0; i < table->capacity; i++) {
    Entry* entry = &table->entries[i];
    if (entry->key == NULL) continue;

    Entry* dest = findEntry(entries, capacity, entry->key);
    dest->key = entry->key;
    dest->value = entry->value;
    table->count++;
  }

  FREE_ARRAY(Entry, table->entries);

  table->entries = entries;
  table->capacity = capacity;
}

// Hashing
uint32_t hashString(const char* key, int length) {
  uint32_t hash = 2166136261u;
  for (int i = 0; i < length; i++) {
    hash ^= (uint8_t)key[i];
    hash *= 16777619;
  }
  return hash;
}

// Table
void initTable(Table* table) {
  table->count = 0;
  table->capacity = 0;
  table->entries = NULL;
}

void freeTable(Table* table) {
  FREE_ARRAY(Entry, table->entries);
  initTable(table);
}

bool tableSet(Table* table, char* key, void* value) {
  if (table->count + 1 > table->capacity * TABLE_MAX_LOAD) {
    int capacity = grow_capacity(table->capacity);
    adjustCapacity(table, capacity);
  }

  Entry* entry = findEntry(table->entries, table->capacity, key);
  bool isNewKey = entry->key == NULL;
  if (isNewKey && entry->value == NULL) table->count++;

  entry->key = key;
  entry->value = value;
  return isNewKey;
}

// bool tableGet(Table* table, char* key, void* value) {
//   if (table->count == 0) return false;
//
//   Entry* entry = findEntry(table->entries, table->capacity, key);
//   if (entry->key == NULL) return false;
//
//   value = entry->value;
//   return true;
// }
//
// bool tableDelete(Table* table, char* key) {
//   if (table->count == 0) return false;
//
//   // Find the entry.
//   Entry* entry = findEntry(table->entries, table->capacity, key);
//   if (entry->key == NULL) return false;
//
//   // Place a tombstone in the entry.
//   entry->key = NULL;
//   entry->value = (void*)true;
//   return true;
// }
//
// void tableAddAll(Table* from, Table* to) {
//   for (int i = 0; i < from->capacity; i++) {
//     Entry* entry = &from->entries[i];
//     if (entry->key != NULL) {
//       tableSet(to, entry->key, entry->value);
//     }
//   }
// }
