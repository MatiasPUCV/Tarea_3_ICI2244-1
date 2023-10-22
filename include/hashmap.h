#ifndef HASHMAP_H
#define HASHMAP_H

#include "pair.h"

#include <stdbool.h>

typedef struct HashMap HashMap;

HashMap* CreateMap();

void InsertMap(HashMap* table, char* key, void* value);
void EraseMap(HashMap* table, const char* key);

Pair* SearchMap(HashMap* table, const char* key);
Pair* FirstMap(HashMap* table);
Pair* NextMap(HashMap* table);

void EnlargeMap(HashMap* map);
void FreeMap(HashMap* map, bool free_key, bool free_value);


int lower_than_string(void* key1, void* key2);

#endif