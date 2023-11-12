#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

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
    return (List *)calloc(1, sizeof(List));
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
    if (list->head->value > value)
    {
        newNode->next = list->head;
        list->head = newNode;
        return ok;
    }

    Node *currentNode = list->head;
    for (; currentNode->next != NULL; currentNode = currentNode->next)
    {
        if (value < currentNode->next->value)
        {
            newNode->next = currentNode->next;
            currentNode->next = newNode;
            return ok;
        }
    }

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
}

ListErrorCode pop(List *const list, int const value)
{
    Node *temp = list->head;
    size_t i = 0;
    for (Node *currentNode = temp; currentNode != NULL; currentNode = currentNode->next)
    {

        if (currentNode->value == value)
        {
            if (i == 0)
            {
                list->head = currentNode->next;
            }
            else
            {
                if (currentNode->next == NULL)
                {
                    temp->next = NULL;
                }
                else
                {
                    temp->next = currentNode->next;
                }
            }
            free(currentNode);
            return ok;
        }
        ++i;
        temp = currentNode;
    }

    return indexError;
}

bool compareListWithArray(List const *const list, int const *const array, const size_t arraySize)
{
    size_t currentIndex = 0;
    for (Node *currentNode = list->head; currentNode != NULL; currentNode = currentNode->next)
    {
        if (currentIndex == arraySize)
        {
            return false;
        }
        if (currentNode->value != array[currentIndex])
        {
            return false;
        }
        ++currentIndex;
    }
    return true;
}
