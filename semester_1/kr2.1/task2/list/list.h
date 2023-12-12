#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef enum ListErrorCode 
{
    okList,
    memoryErrorList,
    indexErrorList
} ListErrorCode;

typedef struct List List;

//creates list
List *createList(void);

//prints list to console
void printList(List const * const list);

//appends int value to list
ListErrorCode append(List *const list, int const value);

//deletes list
void deleteList(List * const list);

//deletes element
ListErrorCode popByIndex(List *const list, size_t const index);

//gets value from list by index
int getValueByIndex(List *list, size_t index, ListErrorCode *listErrorCode);

//checks if value is already in the list
const bool checkValue(List *list, int value)
