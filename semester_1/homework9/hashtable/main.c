#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#include "hashtable/hashtable.h"
#include "workWithFile/workWithFile.h"
#include "list/list.h"
#include "tests/test.h"

#define NUMBER_OF_BUCKETS 100
#define FILENAME "../file.txt"

#define PROGRAM_FINISHED_CORRECTLY 0
#define PROGRAM_FAILED_TESTS 1
#define MEMORY_ERROR 2
#define FILE_READING_ERROR 3

int main(void)
{
    setlocale(LC_ALL, "Rus");

    if (!test())
    {
        printf("Программа сейчас не работает\n");
        return PROGRAM_FAILED_TESTS;
    }


    HashTable *hashTable = createHashTable(NUMBER_OF_BUCKETS);
    if (hashTable == NULL)
    {
        return MEMORY_ERROR;
    }

    if (scanWords(FILENAME, hashTable) != okFile)
    {
        deleteHashTable(hashTable);
        return FILE_READING_ERROR;
    }

    printf("Слова  -  количество появлений в тексте\n\n");
    printHashTable(hashTable);

    size_t averageLength = 0;
    size_t maxLength = 0;
    float koef = 0;
    getStatistics(hashTable, &averageLength, &maxLength, &koef);

    printf("\nМаксимальная длина списка в таблице: %lu\n", maxLength);
    printf("Средняя длина списка в таблице: %lu\n", averageLength);
    printf("Коэффициент заполнения таблицы: %f\n", koef);


    deleteHashTable(hashTable);

    return PROGRAM_FINISHED_CORRECTLY;
}
