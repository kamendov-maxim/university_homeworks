#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "list.h"

typedef struct Node
{
    char *name;
    char *number;
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
    printf("\n");
    for (Node *currentNode = list->head; currentNode != NULL; currentNode = currentNode->next)
    {
        printf("%s - %s\n", currentNode->name, currentNode->number);
    }
    printf("\n");
}

List *createList(ListErrorCode * const listErrorCode)
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

ListErrorCode append(List *const list, char *const name, char *const number)
{

    Node *newNode = (Node *)calloc(1, sizeof(Node));
    if (newNode == NULL)
    {
        return memoryError;
    }

    newNode->name = name;
    newNode->number = number;

    if (list->head == NULL)
    {
        list->head = newNode;
        return ok;
    }

    for (Node *currentNode = list->head; currentNode != NULL; currentNode = currentNode->next)
    {
        if (currentNode->next == NULL)
        {
            currentNode->next = newNode;
            return ok;
        }
    }
    return indexError;
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

void deleteList(List *const list)
{
    while (list->head != NULL)
    {
        Node *currentNode = list->head;
        list->head = currentNode->next;
        free(currentNode);
    }
}

bool isSortedByName(List const * const list)
{
    Node *temp = list->head;
    while (temp->next != NULL)
    {
        if (strcmp(temp->name, temp->next->name) > 0)
        {
            return false;
        }
        temp = temp->next;
    }
    return true;
}

bool isSortedByNumber(List const * const list)
{
    Node *temp = list->head;
    while (temp->next != NULL)
    {
        if (strcmp(temp->number, temp->next->number) > 0)
        {
            return false;
        }
        temp = temp->next;
    }
    return true;
}

static void splitHalf(Node *head, Node **first, Node **second)
{
    int length = 0;

    for (Node *count = head; count->next != NULL; count = count->next, ++length)
        ;

    Node *temp = head;
    for (int i = 0; i < length / 2 - 1; temp = temp->next, ++i)
        ;

    *first = head;
    *second = temp->next;
    temp->next = NULL;
}

static Node *mergeSortedLists(Node *first, Node *second, bool byName)
{
    Node *temp = NULL;

    if (second == NULL)
    {
        return first;
    }
    if (first == NULL)
    {
        return second;
    }

    if (byName)
    {
        if (strcmp(second->name, first->name) < 0)
        {
            temp = second;
            temp->next = mergeSortedLists(second->next, first, byName);
        }
        else
        {
            temp = first;
            temp->next = mergeSortedLists(second, first->next, byName);
        }
    }
    else
    {
        if (strcmp(second->number, first->number) < 0)
        {
            temp = second;
            temp->next = mergeSortedLists(second->next, first, byName);
        }
        else
        {
            temp = first;
            temp->next = mergeSortedLists(second, first->next, byName);
        }
    }
    return temp;
}

static void mergeSortRecursion(Node **head, bool byName)
{
    if ((*head) == NULL || (*head)->next == NULL)
    {
        return;
    }

    Node *first = NULL;
    Node *second = NULL;
    splitHalf(*head, &first, &second);

    mergeSortRecursion(&first, byName);
    mergeSortRecursion(&second, byName);
    *head = mergeSortedLists(first, second, byName);
}

void mergeSortByName(List * const list)
{
    mergeSortRecursion(&(list->head), true);
}

void mergeSortByNumber(List * const list)
{
    mergeSortRecursion(&(list->head), false);
}
