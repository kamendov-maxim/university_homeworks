#pragma once

#include "../hashtable/hashtable.h"

typedef enum FileWorkErrorCode
{
    okFile,
    accessErrorFile,
    memoryErrorFile
} FileWorkErrorCode;

FileWorkErrorCode scanWords(const char *const filename, HashTable * const hashTable);
