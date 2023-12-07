#include <stdlib.h>

#include "hashtable.h"
#include "../list/list.h"

typedef struct HashTable
{
    size_t bucketNumber;
    List ** buckets;
} HashTable;

size_t hash(char *str)
    {
        size_t hash = 5381;
        size_t c = 0;

        while ((c = *str++))
            hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

        return hash;
    }

HashTable * createHashTable(const size_t bucketNumber)
{
    HashTable *hashTable = (HashTable *)calloc(1, sizeof(HashTable));
    if (hashTable == NULL)
    {
        return NULL;
    }

    List ** buckets = (List **)calloc(bucketNumber, sizeof(List *));
    if (buckets == NULL)
    {
        free(hashTable);
        return NULL;
    }
    hashTable->buckets = buckets;

    return hashTable;
}

void deleteHashTable(HashTable * const  hashTable)
{
    for (size_t i = 0; i < hashTable->bucketNumber; i++)
    {
        deleteList(hashTable->buckets[i]);
    }
    free(hashTable->buckets);
    free(hashTable);
    //
}
