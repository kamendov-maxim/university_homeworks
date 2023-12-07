#include <stdlib.h>
#include <string.h>

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
    Node *root;
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

    // if (list->root == NULL)
    // {
    //     Node *newNode = (Node *)calloc(1, sizeof(Node));
    //     if (newNode == NULL)
    //     {
    //         free(valueCopy);
    //         return memoryErrorList;
    //     }
    //     newNode->value = valueCopy;
    //     newNode->entries = 1;
    //     list->root = newNode;
    //     ++list->listLength;
    //     return okList;
    // }

    Node **currentNode = &(list->root);
    for (; *currentNode != NULL; currentNode = &((*currentNode)->next))
    {
        if (strcmp((*currentNode)->value, valueCopy) == 0)
        {
            ++(*currentNode)->entries;
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
    for (Node *currentNode = list->root; currentNode != NULL; currentNode = currentNode->next)
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
    for (Node **currentNode = &(list->root); *currentNode != NULL; currentNode = &((*currentNode)->next))
    {
        if (strcmp(value, (*currentNode)->value) == 0)
        {
            --(*currentNode)->entries;
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
    Node **currentNode = &(list->root);
    while (*currentNode != NULL)
    {
        Node *nextTmp = (*currentNode)->value;
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

size_t getNumberOfEntries(List const * const list, char const * const value)
{
    for (Node *currentNode = list->root; currentNode != NULL; currentNode = currentNode->next)
    {
        if (strcmp(value, currentNode->value) == 0)
        {
            return currentNode->entries;
        }
    }
    return 0;
}