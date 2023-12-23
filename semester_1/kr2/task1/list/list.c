#include <stdlib.h>
#include <stdio.h>

#include "list.h"

typedef struct Node
{
    int value;
    struct Node *next;
} Node;

typedef struct List
{
    Node *head;
} List;

void printList(List const *const list)
{
    printf("\n[");
    for (Node *currentNode = list->head; currentNode != NULL; currentNode = currentNode->next)
    {
        printf("%d", currentNode->value);
        if (currentNode->next != NULL)
        {
            printf(", ");
        }
    }
    printf("]\n");
}

List *createList(void)
{
    List *newList = (List *)calloc(1, sizeof(List));

    return newList;
}

ListErrorCode append(List *const list, int const value)
{
    Node *newNode = (Node *)calloc(1, sizeof(Node));
    if (newNode == NULL)
    {
        return memoryError;
    }

    newNode->value = value;

    if (list->head == NULL)
    {
        list->head = newNode;
        return ok;
    }

    Node *currentNode = list->head;
    for (; currentNode->next != NULL; currentNode = currentNode->next)
        ;

    currentNode->next = newNode;
    return ok;
}

void deleteList(List *const list)
{
    while (list->head != NULL)
    {
        Node *currentNode = list->head;
        list->head = currentNode->next;
        free(currentNode);
    }
    free(list);
}

int getValueByIndex(List *list, size_t index, ListErrorCode *listErrorCode)
{
    size_t currentIndex = 0;
    for (Node *currentNode = list->head; currentNode != NULL; currentNode = currentNode->next)
    {
        if (currentIndex == index)
        {
            *listErrorCode = ok;
            return currentNode->value;
        }

        ++currentIndex;
    }
    *listErrorCode = indexError;
    return -1;
}

ListErrorCode popByIndex(List *const list, size_t const index)
{
    Node *temp = list->head;
    Node *previous = NULL;
    size_t i = 0;
    for (Node *currentNode = temp; currentNode != NULL; currentNode = currentNode->next)
    {
        if (i == index)
        {
            if (i == 0)
            {
                list->head = currentNode->next;
            }
            else
            {
                temp->next = currentNode->next;
            }
            free(currentNode);
            return ok;
        }
        ++i;
        previous = temp;
        temp = currentNode;
    }

    if (index == -1)
    {
        free(temp);
        previous->next = NULL;
        return ok;
    }
    return indexError;
}
