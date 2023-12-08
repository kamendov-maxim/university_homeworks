#include <stdlib.h>

#include "hashtable.h"
#include "../list/list.h"
#include "../String/String.h"

typedef struct HashTable
{
    size_t bucketNumber;
    List **buckets;
} HashTable;

static size_t getHash(char *value)
{
    size_t hash = 5381;
    size_t c = 0;

    while ((c = *value++))
        hash = ((hash << 5) + hash) + c;

    return hash;
}

HashTable *createHashTable(const size_t bucketNumber)
{
    HashTable *hashTable = (HashTable *)calloc(1, sizeof(HashTable));
    if (hashTable == NULL)
    {
        return NULL;
    }

    List **buckets = (List **)calloc(bucketNumber, sizeof(List *));
    if (buckets == NULL)
    {
        free(hashTable);
        return NULL;
    }

    for (size_t i = 0; i < bucketNumber; ++i)
    {
        buckets[i] = createList();
        if (buckets[i] == NULL)
        {
            deleteHashTable(hashTable);
            return NULL;
        }
    }

    hashTable->bucketNumber = bucketNumber;
    hashTable->buckets = buckets;

    return hashTable;
}

HashTableErrorCode addValue(HashTable *const hashTable, char *const value, const bool copyRequired)
{
    char *valueCopy = value;
    if (copyRequired)
    {
        valueCopy = copyString(value);
        if (valueCopy == NULL)
        {
            return memoryErrorHashTable;
        }
    }

    size_t index = getHash(valueCopy) % hashTable->bucketNumber;

    List *list = hashTable->buckets[index];
    ListErrorCode listErrorCode = append(list, valueCopy, false);
    if (listErrorCode != okList)
    {
        free(valueCopy);
        return memoryErrorHashTable;
    }
    return okHashTable;
}

size_t getFrequency(HashTable const *const hashTable, char const *const value)
{
    size_t index = getHash(value) % hashTable->bucketNumber;

    return getNumberOfEntries(hashTable->buckets[index], value);
}

void deleteHashTable(HashTable *const hashTable)
{
    for (size_t i = 0; i < hashTable->bucketNumber; i++)
    {
        deleteList(hashTable->buckets[i]);
    }
    free(hashTable->buckets);
    free(hashTable);
}

void printHashTable(HashTable const *const hashTable)
{
    for (size_t i = 0; i < hashTable->bucketNumber; ++i)
    {
        printList(hashTable->buckets[i]);
    }
}

float getFullnessKoef(HashTable const * const hashTable)
{
    size_t answer = 0;
    for (size_t i = 0; i < hashTable->bucketNumber; ++i)
    {
        if (!isEmpty(hashTable->buckets[i]))
        {
            ++answer;
        }
    }
    return (float)answer / (float)hashTable->bucketNumber;
}

void getStatistics(HashTable const * const hashTable, size_t * const averageLength,
size_t * const maxLength, float * const koef)
{
    size_t k = 0;
    size_t maxLen = 0;
    size_t averageLen = 0;
    size_t currentListLength = 0;
    for (size_t i = 0; i < hashTable->bucketNumber; ++i)
    {
        currentListLength = getLength(hashTable->buckets[i]);
        averageLen += currentListLength;
        maxLen = (currentListLength > maxLen ? currentListLength : maxLen);
        k += (currentListLength != 0 ? 1 : 0);        
    }
    *averageLength =(size_t)averageLen / hashTable->bucketNumber;
    *maxLength = maxLen;
    *koef = (float)k / hashTable->bucketNumber;
}
