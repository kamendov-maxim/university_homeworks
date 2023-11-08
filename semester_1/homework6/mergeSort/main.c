#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>

#include "listMergeSort/list.h"
#include "../getString/getString.h"
#include "tests/test.h"

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
    // return (input == '0' ? byNumber: byName);
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

    FILE *file = fopen("mergeSort/db.txt", "r");
    if (file == NULL)
    {
        return DATA_BASE_FILE_WAS_NOT_FOUND;
    }

    ListErrorCode listErrorCode = ok;
    List *list = createList(&listErrorCode);
    if (listErrorCode != ok)
    {
        return PROBLEM_WITH_LIST;
    }

    size_t len = 0;
    while (!feof(file))
    {
        char *name = getString(&len, file);
        if (name == NULL)
        {
            deleteList(list);
            return MEMORY_ERROR;
        }

        len = 0;
        char *number = getString(&len, file);
        if (number == NULL)
        {
            free(name);
            deleteList(list);
            return MEMORY_ERROR;
        }
        len = 0;

        listErrorCode = append(list, name, number);
        if (listErrorCode != ok)
        {
            free(name);
            free(number);
            deleteList(list);
            return PROBLEM_WITH_LIST;
        }
        free(name);
        free(number);
    }
    fclose(file);
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
