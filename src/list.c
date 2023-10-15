#include "list.h"
#include "util.h"

#include <stdlib.h>

struct List
{
    Node *head;
    Node *tail;
    Node *current;
};

Node* CreateNode(void* data)
{
    Node *temp = (Node*)Malloc(sizeof(Node));
    
    temp->data = data;
    temp->prev = NULL;
    temp->next = NULL;

    return temp;
}

List* CreateList() 
{
    List *list = (List*)Malloc(sizeof(List));

    list->head = NULL;
    list->current = NULL;
    list->tail = NULL;

    return list;
}

void* FirstList(List* list)
{
    if (list == NULL || list->head == NULL)
        return NULL;

    list->current = list->head;

    return list->current->data;
}

void* NextList(List* list)
{
    if (list == NULL || list->current == NULL)
        return NULL;

    list->current = list->current->next;
    if (list->current == NULL)
      return NULL;

    return list->current->data;
}

void* LastList(List* list)
{
    if (list == NULL || list->tail == NULL)
        return NULL;

    list->current = list->tail;

    return list->tail->data;
}

void* PrevList(List* list)
{
    if (list == NULL || list->current == NULL)
      return NULL;

    list->current = list->current->prev;

    if (list->current == NULL)
      return NULL;

    return list->current->data;
}

void PushFront(List* list, void* data)
{
    if (list == NULL || data == NULL)
      return;

    Node *node = CreateNode(data);

    if (list->head == NULL)
    {
        list->head = node;
        list->tail = node;
        return;
    }

    list->head->prev = node;

    node->next = list->head;
    list->head = node;
}

void PushBack(List *list, void *data)
{
    if (list == NULL || data == NULL)
      return;

    list->current = list->tail;
    PushCurrent(list, data);
}

void PushCurrent(List* list, void* data)
{
    if (list == NULL || data == NULL)
      return;

    Node* node = CreateNode(data);
    Node* current = list->current;

    if (current == NULL)
    {
        list->current = node;
        list->head    = node;
        list->tail    = node;
        return;
    }
  
    if (current->next == NULL)
    {
        current->next = node;
        node->prev = current;
        list->tail = node;
        return;
    }

    node->prev = current;
    node->next = current->next;

    current->next->prev = node;
    current->next = node;
}

void* PopFront(List *list)
{
    if (list == NULL)
      return NULL;

    list->current = list->head;
    return PopCurrent(list);
}

void* PopBack(List *list)
{
    if (list == NULL)
      return NULL;

    list->current = list->tail;
    return PopCurrent(list);
}

void* PopCurrent(List* list)
{
    Node* current = list->current;

    if (current == NULL)
        return NULL;
  
    Node* result = current->data;

    if (current->next != NULL && current->prev != NULL)
    {
        current->next->prev = current->prev;
        current->prev->next = current->next;
    }
    else if(current->next == NULL && current->prev != NULL)
    {
        current->prev->next = NULL;
        list->tail = current->prev;
        list->current = current->prev;
    }
    else if(current->prev == NULL && current->next != NULL)
    {
        current->next->prev = NULL;
        list->head = current->next;
        list->current = current->next;
    }
    else if (current->next == NULL && current->prev == NULL)
    {
        list->head = NULL;
        list->current = NULL;
        list->tail = NULL;
    }

    Free(current);
  
    return result;
}


void CleanList(List* list)
{
    while (list->head != NULL)
    {
        void* data = PopFront(list);

        if (data == NULL)
            Free(data);
    }

    Free(list);
}