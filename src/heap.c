#include "heap.h"

#include "util.h"

#include <stdlib.h>

typedef struct heapElem
{
    void* data;
    int priority;

} heapElem;

typedef struct Heap
{
    heapElem* heapArray;
    int size;
    int capac;
} Heap;

void* HeapTop(Heap* pq)
{
    if (pq == NULL)
        return NULL;

    if (pq->size == 0)
        return NULL;

    return pq->heapArray[0].data;
}

void HeapPush(Heap* pq, void* data, int priority)
{
    if (pq == NULL)
        return;
  
    if (pq->capac == pq->size)
    {
        pq->capac = pq->capac*2 + 1;
        pq->heapArray = realloc(pq->heapArray, pq->capac * sizeof(heapElem));
    }

    heapElem new;
    new.data = data;
    new.priority = priority;

    pq->heapArray[pq->size] = new;
    pq->size++;
  
    int index = pq->size - 1;

    while( pq->heapArray[index].priority > pq->heapArray[(index - 1) / 2].priority)
    {
        heapElem temp = pq->heapArray[index];
        pq->heapArray[index] = pq->heapArray[(index - 1) / 2];
        pq->heapArray[(index - 1) / 2] = temp;

        index = (index - 1) / 2;
    }
}

void HeapPopHelper(Heap *pq, int offset, int index)
{
    int child = 2*index + offset;

    if (child > pq->size)
        return;

    if(pq->heapArray[index].priority < pq->heapArray[child].priority)
    {
        heapElem temp = pq->heapArray[index];
        pq->heapArray[index] = pq->heapArray[child];
        pq->heapArray[child] = temp;

        HeapPopHelper(pq, offset, child);

    }
}

void HeapPop(Heap *pq)
{
    if (pq == NULL)
      return;

    pq->heapArray[0] = pq->heapArray[pq->size - 1];
    pq->size--;

    HeapPopHelper(pq, 1, 0);
    HeapPopHelper(pq, 2, 0);
}

Heap* CreateHeap()
{
    Heap* temp = Malloc(sizeof(Heap));
    temp->size = 0;
    temp->capac = 3;
    temp->heapArray = Malloc(sizeof(heapElem) * temp->capac);   
    
    return temp;
}

void FreeHeap(Heap* pq)
{   
    Free(pq->heapArray);
    Free(pq);
}