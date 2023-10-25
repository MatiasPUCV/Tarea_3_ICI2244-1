#include "hashmap.h"
#include "util.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct HashMap
{
    Pair** buckets;
    size_t size;
    size_t capacity;
    size_t current;  
};

size_t Hash(const char *key, size_t capacity)
{
    size_t hash = 0;
    const char* ptr;

    for (ptr = key; *ptr != '\0'; ptr++)
        hash += hash * 32 + tolower(*ptr);
    
    return hash % capacity;
}

int IsEqual(const void *key1, const void *key2)
{
    if (key1 == NULL || key2 == NULL)
        return 0;

    if (strcmp((char *)key1, (char *)key2) == 0)
        return 1;

    return 0;
}

HashMap* CreateMap()
{
    const size_t capacity = 256;

    HashMap* hashMap = (HashMap*)Malloc(sizeof(HashMap));

    hashMap->buckets = (Pair**)Calloc(capacity, sizeof(Pair*));
    hashMap->size = 0;

    hashMap->capacity = capacity;
    hashMap->current = -1;

    return hashMap;
}

void InsertMap(HashMap* table, char* key, void* value)
{
    if (table == NULL || key == NULL || value == NULL)
        return;
    
    if (table->capacity == table->size)
        return;

    long pos = Hash(key, table->capacity);
    long temp = pos;

    while (!IsEmptyPair(table->buckets[pos]))
    {
        pos = (pos + 1) % table->capacity;
        if (pos == temp)
            return;
    }

    table->buckets[pos] = CreatePair(key, value);

    table->current = pos;
    table->size += 1;

    long cap70 = table->capacity * 0.7;

    if (table->size >= cap70)
        EnlargeMap(table);
}

void EnlargeMap(HashMap* table)
{
    if (table == NULL)
        return;

    Pair** oldBuckets = table->buckets;
    size_t oldCapacity = table->capacity;

    table->size = 0;
    table->capacity *= 2;

    table->buckets = (Pair**)Calloc(table->capacity, sizeof(Pair*));

    for (size_t i = 0; i < oldCapacity; i++)
    {
        Pair* temp = oldBuckets[i];

        if (temp != NULL)
        {
            InsertMap(table, temp->key, temp->value);
            Free(temp);
        }
    }

    Free(oldBuckets);
}

void EraseMap(HashMap* table, const char* key)
{
    if (table == NULL || key == NULL)
        return;

    Pair* temp = SearchMap(table, key);
    if (temp != NULL)
    {
        temp->key = NULL;
        table->size -= 1;
    }
}

Pair* SearchMap(HashMap* table, const char* key)
{
    if (table == NULL || key == NULL)
        return NULL;

    size_t pos = Hash(key, table->capacity);
    size_t temp = pos;

    bool stop = false;

    while (!stop)
    {
        if (table->buckets[pos] != NULL && IsEqual(key, table->buckets[pos]->key))
        {
            stop = true;
        }
        else
        {
            pos = (pos + 1) % table->capacity;
            if (pos == temp)
                return NULL;
        }
    }

    table->current = pos;

    return table->buckets[pos];
}

Pair* FirstMap(HashMap* table)
{
    if (table == NULL)
        return NULL;

    size_t pos = table->current;
    size_t temp = pos;

    while (IsEmptyPair(table->buckets[pos]))
    {
        pos = (pos + 1) % table->capacity;

        if (pos == temp)
            return NULL;
    }

    table->current = pos;

    return table->buckets[pos];
}

Pair* NextMap(HashMap* table)
{
    if (table == NULL)
        return NULL;

    size_t pos = table->current + 1;

    if (pos >= table->capacity - 1)
        pos = 0;

    table->current = pos;
  
    return FirstMap(table);
}

void FreeMap(HashMap* map, bool free_key, bool free_value)
{
    if (map == NULL)
        return;

    for (size_t i = 0; i < map->capacity; i++)
    {
        Pair* temp = map->buckets[i];
        if (temp == NULL)
            continue;

        if (free_key == true && temp->key != NULL)
            Free(temp->key);


        if(free_value == true && temp->value != NULL)
            Free(temp->value);


        Free(temp);
    }

    Free(map->buckets);
    Free(map);
}