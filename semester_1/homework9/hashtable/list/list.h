#pragma once

#include <stdlib.h>
#include <stdbool.h>

typedef enum ListErrorCode
{
    okList,
    memoryErrorList
} ListErrorCode;

typedef struct List List;

List *createList(void);
ListErrorCode append(List * const list, char * const value, const bool copyRequired);
bool checkElement(List const * const list, char const * const value);
void deleteElement(List * const list, char const * const value);
void deleteList(List * const list);
size_t getLength(List const * const list);
size_t getNumberOfEntries(List const * const list, char const * const value);
void printList(List  *const list);
const bool isEmpty(List const * const list);
