#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef enum ListErrorCode 
{
    ok,
    memoryError
} ListErrorCode;

typedef struct List List;

List *createList(ListErrorCode * const listErrorCode);
void printList(List const * const list);
ListErrorCode append(List * const list, char * const number, char * const name);
void deleteList(List * const list);
void mergeSortByNumber(List * const list);
void mergeSortByName(List * const list);
bool isSortedByNumber(List const * const list);
bool isSortedByName(List const * const list);
