#include "pair.h"
#include "util.h"

#include <stdlib.h>

Pair* CreatePair(char* key, void* value)
{
    if (key == NULL || value == NULL)
        return NULL;

    Pair* temp = (Pair*)Malloc(sizeof(Pair));

    temp->key = key;
    temp->value = value;

    return temp;
}

bool IsEmptyPair(Pair* pair)
{
    if (pair == NULL)
        return true;

    if (pair->key == NULL)
        return true;

    return false;
}
