#include "hashmap.h"
#include "util.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

struct HashMap
{
    Pair** buckets;
    long size;
    long capacity;
    long current;  
};

long Hash(const char *key, long capacity)
{
    unsigned long hash = 0;
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
    const long capacity = 2;

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

    Success("Enlarge!");

    Pair** oldBuckets = table->buckets;
    long oldCapacity = table->capacity;

    table->size = 0;
    table->capacity *= 2;

    table->buckets = (Pair**)Calloc(table->capacity, sizeof(Pair*));

    for (long l = 0; l < oldCapacity; l++)
    {
        Pair* temp = oldBuckets[l];

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

    long pos = Hash(key, table->capacity);
    long temp = pos;

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


// TODO: FIX

Pair* FirstMap(HashMap* table)
{
    if (table == NULL)
        return NULL;

    long pos = table->current;
    long temp = pos;

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

    long pos = table->current + 1;

    if (pos >= table->capacity - 1)
        pos = 0;

    table->current = pos;
  
    return FirstMap(table);
}

void FreeMap(HashMap* map)
{
    Free(map->buckets);
    Free(map);
}