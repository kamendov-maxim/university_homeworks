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
        printf("%s-%s\n", currentNode->name, currentNode->number);
    }
    printf("\n");
}

List *createList(void)
{
    List *newList = (List *)calloc(1, sizeof(List));
    if (newList == NULL)
    {
        return NULL;
    }

    return newList;
}

ListErrorCode append(List *const list, char *const name, char *const number, bool const copyRequired)
{
    char *nameCopy;
    char *numberCopy;
    if (copyRequired)
    {
        const size_t nameLen = strlen(name);
        nameCopy = (char *)malloc(nameLen * sizeof(char));
        if (nameCopy == NULL)
        {
            return memoryError;
        }
        strcpy(nameCopy, name);

        const size_t numberLen = strlen(number);
        numberCopy = (char *)malloc(numberLen * sizeof(char));
        if (numberCopy == NULL)
        {
            free(nameCopy);
            return memoryError;
        }
        strcpy(numberCopy, number);
    }
    else
    {
        nameCopy = name;
        numberCopy = number;
    }

    Node *newNode = (Node *)calloc(1, sizeof(Node));
    if (newNode == NULL)
    {
        if (copyRequired)
        {
            free(nameCopy);
            free(numberCopy);
        }
        return memoryError;
    }

    newNode->name = nameCopy;
    newNode->number = numberCopy;

    if (list->head == NULL)
    {
        list->head = newNode;
        return ok;
    }

    Node *currentNode = list->head;
    for (; currentNode->next != NULL; currentNode = currentNode->next);

    currentNode->next = newNode;
    return ok;
}

void deleteList(List *const list)
{
    while (list->head != NULL)
    {
        Node *currentNode = list->head;
        list->head = currentNode->next;
        free(currentNode->name);
        free(currentNode->number);
        free(currentNode);
    }
}

static char *getNodeField(Node const *const node, bool byName)
{
    return (byName ? node->name : node->number);
}

static bool isSorted(List const *const list, bool byName)
{
    Node *temp = list->head;
    for (; temp->next != NULL; temp = temp->next)
    {
        if (strcmp(getNodeField(temp, byName), getNodeField(temp->next, byName)) > 0)
        {
            return false;
        }
    }
    return true;
}

bool isSortedByName(List const *const list)
{
    return isSorted(list, true);
}

bool isSortedByNumber(List const *const list)
{
    return isSorted(list, false);
}

static void splitHalf(Node *const head, Node **const first, Node **const second)
{
    size_t length = 0;

    for (Node *count = head; count->next != NULL; count = count->next, ++length);

    Node *temp = head;
    for (size_t i = 0; i < length / 2; temp = temp->next, ++i);

    *first = head;
    *second = temp->next;
    temp->next = NULL;
}

static Node *mergeSortJoin(Node *first, Node *second, bool byName)
{
    Node *temp = (Node *)calloc(1, sizeof(Node));
    Node *ptr = temp;
    for (; first != NULL && second != NULL; temp = temp->next)
    {

        if (strcmp(getNodeField(second, byName), getNodeField(first, byName)) < 0)
        {
            temp->next = second;
            second = second->next;
        }
        else
        {
            temp->next = first;
            first = first->next;
        }
    }

    temp->next = (second == NULL ? first : second);
    temp = ptr;
    ptr = ptr->next;
    free(temp);

    return ptr;
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

    *head = mergeSortJoin(first, second, byName);
}

void mergeSortByName(List *const list)
{
    mergeSortRecursion(&(list->head), true);
}

void mergeSortByNumber(List *const list)
{
    mergeSortRecursion(&(list->head), false);
}
