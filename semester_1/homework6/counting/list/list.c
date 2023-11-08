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

List *createList(void)
{
    List *newList = (List *)calloc(1, sizeof(List));
    if (newList == NULL)
    {
        return NULL;
    }

    return newList;
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

static List *appendWarriors(const int n)
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

static int killing(List *warriors, const int m)
{
    Node *warrior = warriors->head;
    int t = m - 1;
    while (warrior->next->value != warrior->value)
    {
        for (int count = 1; count != t; warrior = warrior->next, ++count);

        if (warrior->next != NULL && warrior->next->next != NULL)
        {
            Node *temp = warrior->next;
            warrior->next = warrior->next->next;
            free(temp);
        }
        t = m;
    }

    return (warrior->value);
}

int count(const int n, const int m, ListErrorCode *const listErrorCode)
{
    List *warriors = appendWarriors(n);
    if (warriors == NULL)
    {
        *listErrorCode = memoryError;
        return -1;
    }

    return killing(warriors, m);
}
