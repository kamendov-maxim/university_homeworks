#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef enum ListErrorCode
{
    ok,
    memoryError,
    indexError
} ListErrorCode;

typedef struct List List;

List *createList(void);
void printList(List const *const list);
ListErrorCode append(List *const list, int const value);
void deleteList(List *const list);
ListErrorCode pop(List *const list, int const value);
bool compareListWithArray(List const *const list, int const *const array, const size_t arraySize);

