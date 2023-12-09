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

ListErrorCode append(List *const list, char *const value, const bool copyRequired)
{
    char *valueCopy = value;
    if (copyRequired)
    {
        valueCopy = copyString(value);
        if (valueCopy == NULL)
        {
            return memoryErrorList;
        }
    }

    Node **currentNode = &(list->head);
    for (; *currentNode != NULL; currentNode = &((*currentNode)->next))
    {
        if (strcmp((*currentNode)->value, valueCopy) == 0)
        {
            ++(*currentNode)->entries;
            ++list->listLength;

            return okList;
        }
    }

    Node *newNode = (Node *)calloc(1, sizeof(Node));
    if (newNode == NULL)
    {
        free(valueCopy);
        return memoryErrorList;
    }
    newNode->value = valueCopy;
    *currentNode = newNode;
    (*currentNode)->entries = 1;

    ++list->listLength;
    return okList;
}

bool checkElement(List const *const list, char const *const value)
{
    for (Node *currentNode = list->head; currentNode != NULL; currentNode = currentNode->next)
    {
        if (strcmp(value, currentNode->value) == 0)
        {
            return true;
        }
    }
    return false;
}

void deleteElement(List *const list, char const *const value)
{
    for (Node **currentNode = &(list->head); *currentNode != NULL; currentNode = &((*currentNode)->next))
    {
        if (strcmp(value, (*currentNode)->value) == 0)
        {
            --(*currentNode)->entries;
            --list->listLength;
            if ((*currentNode)->entries != 0)
            {
                return;
            }

            free((*currentNode)->value);
            Node *nextTmp = (*currentNode)->next;
            free(*currentNode);
            *currentNode = nextTmp;
            return;
        }
    }
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
    for (Node *currentNode = list->head; currentNode != NULL; currentNode = currentNode->next)
    {
        if (strcmp(value, currentNode->value) == 0)
        {
            return currentNode->entries;
        }
    }
    return 0;
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
