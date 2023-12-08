#pragma once

#include <stdlib.h>
#include <stdbool.h>

typedef enum HashTableErrorCode
{
    okHashTable,
    memoryErrorHashTable
} HashTableErrorCode;

typedef struct HashTable HashTable;

HashTable *createHashTable(const size_t bucketNumber);
HashTableErrorCode addValue(HashTable *const hashTable, char *const value, const bool copyRequired);
void printHashTable(HashTable const *const hashTable);
void deleteHashTable(HashTable *const hashTable);
size_t getFrequency(HashTable const *const hashTable, char const *const value);
float getFullnessKoef(HashTable const * const hashTable);
void getStatistics(HashTable const * const hashTable, size_t * const averageLength, size_t * const maxLength, float * const koef);
