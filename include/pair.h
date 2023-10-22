#ifndef PAIR_H
#define PAIR_H

#include <stdbool.h>

typedef struct Pair
{
    void* key;
    void* value;
} Pair;

Pair* CreatePair(char* key, void* value);
bool IsEmptyPair(Pair* pair);

#endif // PAIR_H