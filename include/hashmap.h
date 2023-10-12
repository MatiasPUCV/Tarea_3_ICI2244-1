#ifndef HASHMAP_H
#define HASHMAP_H

typedef struct HashMap HashMap;

typedef struct Pair 
{
    const char* key;
    void* value;
} Pair;

HashMap* CreateMap();

void InsertMap(HashMap* table, const char* key, void* value);
void EraseMap(HashMap* table, const char* key);

Pair* SearchMap(HashMap* table, const char* key);
Pair* FirstMap(HashMap* table);
Pair* NextMap(HashMap* table);

void EnlargeMap(HashMap* map);

#endif