#include <stdlib.h>

#include "list.h"

typedef struct Node
{
    struct Node *next;
    char *value;
} Node;

typedef struct List
{
    size_t length;
    Node *head;
    Node *back;
} List;

List *createList(void)
{
    return calloc(1, sizeof(List));
}

ErrorCode addElement(List *list, char *const value)
{
    Node *newNode = calloc(1, sizeof(Node));
    if (newNode == NULL)
    {
        return memoryError;
    }

    newNode->value = value;

    if (list->head == NULL)
    {
        list->head = newNode;
        list->back = newNode;
        ++list->length;
        return ok;
    }

    list->back->next = newNode;
    list->back = newNode;
    ++list->length;
    return ok;
}

char **writeToDefaultArray(List const *const list, size_t *length)
{
    char **output = calloc(list->length, sizeof(char *));
    if (output == NULL)
    {
        return NULL;
    }

    size_t i = 0;
    for (Node *node = list->head; node != NULL; node = node->next)
    {
        output[i] = node->value;
        ++i;
    }

    *length = list->length;
    return output;
}

void deleteList(List **const list)
{
    Node *currentNode = (*list)->head;
    while (currentNode != NULL)
    {
        Node *temp = currentNode;
        currentNode = currentNode->next;
        // free(temp->value);
        free(temp);
    }
    free(*list);
    *list = NULL;
}
