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

List *createList(ListErrorCode *const listErrorCode);
void printList(List const *const list);
ListErrorCode append(List *const list, int const value);
void deleteList(List *const list);
bool isSorted(List const *const list);
ListErrorCode popByIndex(List *const list, size_t const index);
