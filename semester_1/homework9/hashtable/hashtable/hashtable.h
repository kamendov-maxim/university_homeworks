#pragma once

#include <stdlib.h>

typedef enum HashTableErrorCode
{
    okHashTable,
    memoryErrorHashTable
} HashTableErrorCode;

size_t hash(char *str);
