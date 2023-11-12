#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "../String/String.h"

typedef enum ListErrorCode 
{
    ok,
    memoryError
} ListErrorCode;

typedef struct List List;

List *createList(void);
void printList(List const * const list);
ListErrorCode append(List *const list, char *const name, char *const number, bool const copyRequired);
void deleteList(List * const list);
void mergeSortByNumber(List * const list, ListErrorCode *listErrorCode);
void mergeSortByName(List * const list, ListErrorCode *listErrorCode);
bool isSortedByNumber(List const * const list);
bool isSortedByName(List const * const list);
