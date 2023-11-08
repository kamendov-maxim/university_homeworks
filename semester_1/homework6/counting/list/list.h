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

List *createList(void);
void deleteList(List *const list);
int count(const int n, const int m, ListErrorCode * const listErrorCode);
