#include <stdio.h>

#include "workWithFile.h"
#include "../String/String.h"
#include "../hashtable/hashtable.h"

FileWorkErrorCode scanWords(const char *const filename, HashTable *hashTable)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        return accessErrorFile;
    }

    char *word = NULL;
    size_t len = 0;
    do
    {
        word = getString(&len, file, ' ');
        if (word == NULL)
        {
            fclose(file);
            return memoryErrorFile;
        }

        if (word[0] != '\0')
        {
            HashTableErrorCode hashTableErrorCode = addValue(hashTable, word, false);
            if (hashTableErrorCode != okHashTable)
            {
                fclose(file);
                return memoryErrorFile;
            }
        }

    } while (word[0] != '\0');
    fclose(file);
    return okFile;
}
