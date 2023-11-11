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

static List *createList(void)
{
    List *newList = (List *)calloc(1, sizeof(List));
    return newList;
}

static void deleteList(List *const list)
{
    while (list->head->next != list->head && list->head != NULL)
    {
        Node *currentNode = list->head;
        list->head = currentNode->next;
        // if (list->head != currentNode->next)
        // {
        // }
        free(currentNode);
    }
    // free(list->head);
    // free(list);
}

static List *appendWarriors(const size_t n)
{
    Node *head = NULL;
    List *warriors = createList();
    if (warriors == NULL)
    {
        return NULL;
    }

    for (int i = n; i > 0; --i)
    {
        Node *warrior = malloc(sizeof(Node));
        if (warrior == NULL)
        {
            return NULL;
        }

        warrior->value = i;
        warrior->next = head;
        head = warrior;
    }

    Node *temp = head;
    for (; temp->next != NULL; temp = temp->next);

    temp->next = head;
    warriors->head = head;
    return warriors;
}

static size_t killing(List *warriors, const size_t m)
{
    Node *warrior = warriors->head;
    size_t t = m - 1;
    while (warrior->next != warrior)
    {
        for (size_t count = 1; count != t; warrior = warrior->next, ++count);

        Node *temp = warrior->next;
        warrior->next = warrior->next->next;
        free(temp);
        t = m;
    }

    return (warrior->value);
}

size_t count(const size_t n, const size_t m, ListErrorCode *const listErrorCode)
{
    List *warriors = appendWarriors(n);
    if (warriors == NULL)
    {
        *listErrorCode = memoryError;
        return -1;
    }

    // deleteList(warriors);
    return killing(warriors, m);
}
