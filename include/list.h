#ifndef LIST_H
#define LIST_H

typedef struct Node Node;

struct Node
{
    void* data;
    Node* next;
    Node* prev;
};

typedef struct List List;

List* CreateList(void);
void CleanList(List* list, void (*free_func)(void* ptr));

void* FirstList(List* list);
void* NextList(List* list);
void* LastList(List* list);
void* PrevList(List* list);
void* CurrentList(List* list);

void PushFront(List* list, void* data);
void PushBack(List* list, void* data);
void PushCurrent(List* list, void* data);

void* PopFront(List* list);
void* PopBack(List* list);
void* PopCurrent(List* list);

#endif // LIST_H