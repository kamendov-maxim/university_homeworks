#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>

#include "../list/list.h"
#include "../get_string/get_string.h"
#include "tests/test.h"

#define PROGRAM_FINISHED_CORRECTLY 0
#define DATA_BASE_FILE_WAS_NOT_FOUND 1
#define MEMORY_ERROR 2
#define PROBLEM_WITH_LIST 3
#define INPUT_ERROR 4
#define TESTS_ARE_NOT_PASSED 5

int main(void)
{
    if (!test())
    {
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
        char *name = get_string(&len, file);
        if (name == NULL)
        {
            deleteList(list);
            return MEMORY_ERROR;
        }

        len = 0;
        char *number = get_string(&len, file);
        if (number == NULL)
        {
            deleteList(list);
            return MEMORY_ERROR;
        }
        len = 0;

        listErrorCode = append(list, name, number);
        if (listErrorCode != ok)
        {
            deleteList(list);
            return PROBLEM_WITH_LIST;
        }
    }
    fclose(file);
    printList(list);

    printf("Как вы хотите отсортировать записи?\n");
    printf("0 - по номеру телефона\n");
    printf("1 - по имени\n");
    printf("Введите цифру: \n");

    char input = '0';
    int scanned = scanf("%s", &input);
    if (scanned != 1)
    {
        deleteList(list);
        return INPUT_ERROR;
    }
    while (input != '1' && input != '0')
    {
        printf("Вы должны ввести 1 или 0\n");
        scanned = scanf("%s", &input);
        if (scanned != 1)
        {
            deleteList(list);
            return INPUT_ERROR;
        }
    }
    if (input == '0')
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
