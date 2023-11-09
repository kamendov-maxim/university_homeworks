#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>

#include "listMergeSort/list.h"
#include "../getString/getString.h"
#include "tests/test.h"
#include "fileReading/fileReading.h"

typedef enum UserInput
{
    byNumber,
    byName,
    error
} UserInput;

#define PROGRAM_FINISHED_CORRECTLY 0
#define DATA_BASE_FILE_WAS_NOT_FOUND 1
#define MEMORY_ERROR 2
#define PROBLEM_WITH_LIST 3
#define INPUT_ERROR 4
#define TESTS_ARE_NOT_PASSED 5

#define FILENAME "mergeSort/db.txt"

static const UserInput getSortType(void)
{
    printf("Как вы хотите отсортировать записи?\n");
    printf("0 - по номеру телефона\n");
    printf("1 - по имени\n");
    printf("Введите цифру: \n");

    UserInput input = byName;
    size_t scanned = scanf("%d", &input);
    if (scanned != 1)
    {
        return error;
    }

    while (input != byNumber && input != byName)
    {
        printf("Вы должны ввести 1 или 0\n");
        size_t scanned = scanf("%d", &input);
        if (scanned != 1)
        {
            return error;
        }
    }
    return input;
}

int main(void)
{
    if (!test())
    {
        printf("Простите, но программа сейчас не работает\n");
        return TESTS_ARE_NOT_PASSED;
    }
    setlocale(LC_ALL, "Rus");

    List *list = createList();
    if (list == NULL)
    {
        return MEMORY_ERROR;
    }
    ListErrorCode listErrorCode = ok;
    int errorCode = fileReading(list, FILENAME, false);
    if (errorCode != 0)
    {
        printf("Возникла ошибка при чтении из базы данных\n");
        return errorCode;
    }

    printList(list);

    UserInput input = getSortType();
    if (input == error)
    {
        deleteList(list);
        return INPUT_ERROR;
    }

    if (input == byNumber)
    {
        mergeSortByNumber(list);
    }
    else
    {
        mergeSortByName(list);
    }

    printList(list);
    deleteList(list);
    return PROGRAM_FINISHED_CORRECTLY;
}
