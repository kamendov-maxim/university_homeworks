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
    if (list->head == NULL)
    {
        return;
    }
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

List *createList(ListErrorCode *const listErrorCode)
{
    List *newList = (List *)calloc(1, sizeof(List));
    if (newList == NULL)
    {
        *listErrorCode = memoryError;
        return NULL;
    }

    *listErrorCode = ok;
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
    if (list->head->value > value)
    {
        newNode->next = list->head;
        list->head = newNode;
        return ok;
    }

    Node *currentNode = list->head;
    for (; currentNode->next != NULL; currentNode = currentNode->next)
    {
        if (currentNode->next != NULL && value < currentNode->next->value)
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

bool isSorted(List const *const list)
{
    Node *temp = list->head;
    for (; temp->next != NULL; temp = temp->next)
    {
        if (temp->next != NULL)
        {
            if (temp->value > temp->next->value)
            {
                printf("\n%d %d %d\n", temp->value, temp->next->value, temp->value > temp->next->value);
                return false;
            }
        }
    }
    return true;
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
