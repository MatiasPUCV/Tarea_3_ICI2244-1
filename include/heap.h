#ifndef HEAP_H
#define HEAP_H

typedef struct Heap Heap;

Heap* CreateHeap();
void FreeHeap(Heap* pq);

void* HeapTop(Heap* pq);
void HeapPush(Heap* pq, void* data, int priority);
void HeapPop(Heap* pq);


#endif // HEAP_H