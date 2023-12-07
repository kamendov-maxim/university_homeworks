#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "../String/String.h"

typedef struct Node
{
    struct Node *next;
    struct Node *previous;
    char *value;
} Node;


typedef struct List
{
    Node *root;
} List;

List *createList(void)
{
    return calloc(1, sizeof(List));
}

ListErrorCode append(List * const list, char * const value, const bool copyRequired)
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

    Node *newNode = (Node *)calloc(1, sizeof(Node));
    if (newNode == NULL)
    {
        free(valueCopy);
        return memoryErrorList;
    }
    newNode->value = valueCopy;

    if (list->root == NULL)
    {
        list->root = newNode;
        return okList;
    }

    Node **currentNode = &(list->root);
    for (; *currentNode != NULL; currentNode = &((*currentNode)->next));

    *currentNode = newNode;
    
    return okList;    
}

bool checkElement(List const * const list, char const * const value)
{
    for (Node * currentNode = list->root; currentNode != NULL; currentNode = currentNode->next)
    {
        if (strcmp(value, currentNode->value) == 0)
        {
            return true;
        }
    }
    return false;
}

void deleteElement(List * const list, char const * const value)
{
    for (Node **currentNode = &(list->root); *currentNode != NULL; currentNode = &((*currentNode)->next))
    {
        if (strcmp(value, (*currentNode)->value) == 0)
        {
            free((*currentNode)->value);
            Node *nextTmp = (*currentNode)->next;
            free(*currentNode);
            *currentNode = nextTmp;
            return;
        }
    }
}

void deleteList(List * const list)
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
