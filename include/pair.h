#ifndef PAIR_H
#define PAIR_H

typedef struct Pair
{
    void* key;
    void* value;
} Pair;

Pair* CreatePair(char* key, void* value);

#endif // PAIR_H