#ifndef TREEMAP_H
#define TREEMAP_H

#include "pair.h"

typedef struct TreeMap TreeMap;

TreeMap* CreateTreeMap(int (*lower_than_int) (void* key1, void* key2));
void InsertTreeMap(TreeMap* tree, void* key, void* value);
void EraseTreeMap(TreeMap* tree, void* key);

Pair* SearchTreeMap(TreeMap* tree, void* key);
Pair* UpperBound(TreeMap* tree, void* key);
Pair* FirstTreeMap(TreeMap* tree);
Pair* NextTreeMap(TreeMap* tree);

int lower_than_string(void* key1, void* key2);
int lower_than_int(void* key1, void* key2);
int higher_than_int(void* key1, void* key2);

#endif // REEMAP_H