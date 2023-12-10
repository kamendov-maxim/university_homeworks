#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "list.h"
#include "../String/String.h"

typedef struct Node
{
    struct Node *next;
    struct Node *previous;
    size_t entries;
    char *value;
} Node;

typedef struct List
{
    Node *head;
    size_t listLength;
} List;

List *createList(void)
{
    return calloc(1, sizeof(List));
}

static Node **findNode(List const *const list, char const *const value)
{
    Node **currentNode = &(list->head);
    for (; *currentNode != NULL; currentNode = &((*currentNode)->next))
    {
        if (strcmp(value, (*currentNode)->value) == 0)
        {
            return currentNode;
        }
    }

    return currentNode;
}

ListErrorCode append(List *const list, char *const value, const bool copyRequired)
{
    Node **node = findNode(list, value);
    if (*node != NULL)
    {
        ++(*node)->entries;
        ++list->listLength;

        return okList;
    }

    Node *newNode = (Node *)calloc(1, sizeof(Node));
    if (newNode == NULL)
    {
        return memoryErrorList;
    }

    char *valueCopy = value;
    if (copyRequired)
    {
        valueCopy = copyString(value);
        if (valueCopy == NULL)
        {
            free(newNode);
            return memoryErrorList;
        }
    }
    newNode->value = valueCopy;
    *node = newNode;
    (*node)->entries = 1;

    ++list->listLength;
    return okList;
}

bool checkElement(List const *const list, char const *const value)
{
    return *(findNode(list, value)) != NULL;
}

void deleteElement(List *const list, char const *const value)
{
    Node **node = findNode(list, value);
    if (*node == NULL)
    {
        return;
    }
    --(*node)->entries;
    --list->listLength;
    if ((*node)->entries != 0)
    {
        return;
    }

    free((*node)->value);
    Node *nextTmp = (*node)->next;
    free(*node);
    *node = nextTmp;
}

void deleteList(List *const list)
{
    Node **currentNode = &(list->head);
    while (*currentNode != NULL)
    {
        Node *nextTmp = (*currentNode)->next;
        free((*currentNode)->value);
        free(*currentNode);
        *currentNode = nextTmp;
    }
    free(list);
}

size_t getLength(List const *const list)
{
    return list->listLength;
}

size_t getNumberOfEntries(List const *const list, char const *const value)
{
    Node **node = findNode(list, value);
    return (*node == NULL ? 0 : (*node)->entries);
}

void printList(List *const list)
{
    for (Node **currentNode = &(list->head); *currentNode != NULL; currentNode = &((*currentNode)->next))
    {
        printf("%s - %lu\n", (*currentNode)->value, (*currentNode)->entries);
    }
}

const bool isEmpty(List const *const list)
{
    return list->head == NULL;
}
