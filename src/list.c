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
    Node *temp = Malloc(sizeof(Node));

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

void HelperEmptyList(List* list, void* data)
{
    Node* node = CreateNode(data);

    list->head = node;
    list->tail = node;
}

void PushFront(List* list, void* data)
{
    if (list == NULL || data == NULL)
      return;

    // La lista esta vacia
    if (list->head == NULL)
    {
        HelperEmptyList(list, data);
        return;
    }
  
    Node* node = CreateNode(data);

    list->head->prev = node;
    node->next = list->head;

    list->head = node;
}

void PushBack(List *list, void *data)
{
    if (list == NULL || data == NULL)
      return;

    // La lista esta vacia
    if (list->head == NULL)
    {
        HelperEmptyList(list, data);
        return;
    }

    Node* node = CreateNode(data);

    list->tail->next = node;
    node->prev = list->tail;

    list->tail = node;
}

void pushCurrent(List* list, void* data)
{
    if (list == NULL || data == NULL)
      return;

    // La lista esta vacia
    if (list->head == NULL)
    {
        HelperEmptyList(list, data);
        return;
    }

    Node* node = CreateNode(data);

    node->prev = list->current;

    if (list->current->next != NULL)
    {
        node->next = list->current->next;
        list->current->next->prev = node;
    }
      
    else
      list->tail = node;

    list->current->next = node;

}

void* HelperPopNode(Node* node)
{
    void* data = node->data;
    Free(node);

    return data;
}

void* PopFront(List *list)
{
    if (list == NULL || list->head == NULL)
      return NULL;

    Node* node = list->head;
  
    list->head = list->head->next;

    if (list->head != NULL)
        list->head->prev = NULL;

    list->current = list->head;

    return HelperPopNode(node);
}

void* PopBack(List *list)
{
    if (list == NULL || list->tail == NULL)
      return NULL;

    Node* node = list->tail;

    list->tail = list->tail->prev;

    if (list->tail == NULL)
        list->tail->next = NULL;

    list->current = list->tail;

    return HelperPopNode(node);
}

void* PopCurrent(List* list)
{
    if (list->current == NULL)
        return NULL;

    if (list->current->next == NULL)
        return PopBack(list);

    if (list->current->prev == NULL)
        return PopFront(list);

    Node* node = list->current;
  
    node->prev->next = node->next;
    node->next->prev = node->prev;

    list->current = node->next;

    return HelperPopNode(node);
}

void CleanList(List* list, void (*free_func)(void* ptr))
{
    while (list->head != NULL)
    {
        void* data = PopFront(list);

        if (data == NULL)
            free_func(data);
    }

    Free(list);
}