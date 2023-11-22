#include <stdio.h>
#include <locale.h>
#include <stdbool.h>

#include "list/list.h"

#define PROGRAM_FINISHED_CORRECTLY 0
#define MEMORY_ERROR 1
#define PROBLEM_WITH_LIST 2
#define PROGRAM_FAILED_TESTS 3
#define SOMETHING_WENT_WRONG_MESSAGE "Похоже, что-то пощло не так\n"

void deleteOddElements(List *const list);
const bool test(void);

int main(void)
{
    setlocale(LC_ALL, "Rus");

    if (!test())
    {
        printf("Простите, но программа сейчас не работает\n");
        return PROGRAM_FAILED_TESTS;
    }

    List *list = createList();
    if (list == NULL)
    {
        printf("Недостаточно памяти\n");
        return MEMORY_ERROR;
    }

    ListErrorCode listErrorCode = ok;
    int values[5] = {1, 2, 3, 4, 5};
    for (size_t i = 0; i < 5; ++i)
    {
        listErrorCode = append(list, values[i]);
        if (listErrorCode != ok)
        {
            printf("%s", SOMETHING_WENT_WRONG_MESSAGE);
            deleteList(list);
            return 1;
        }
    }

    printf("До\n");
    printList(list);

    deleteOddElements(list);

    printf("После\n");
    printList(list);

    deleteList(list);
    return 0;
}

void deleteOddElements(List *const list)
{
    ListErrorCode listErrorCode = ok;
    for (size_t currentIndex = 1; listErrorCode == ok; currentIndex += 1)
    {
        listErrorCode = popByIndex(list, currentIndex);
    }
}

static const bool testCase(int *array, size_t sizeOfArray, int *answerArray, size_t answerArraySize)
{
    List *list = createList();
    if (list == NULL)
    {
        return false;
    }

    ListErrorCode listErrorCode = ok;
    for (size_t i = 0; i < sizeOfArray; ++i)
    {
        listErrorCode = append(list, array[i]);
        if (listErrorCode != ok)
        {
            printf("%d\n", array[i]);
            deleteList(list);
            return false;
        }
    }

    deleteOddElements(list);

    for (size_t i = 0; i < answerArraySize; ++i)
    {
        if (answerArray[i] != getValueByIndex(list, i, &listErrorCode) || listErrorCode != ok)
        {
            printf("%d %d\n", answerArray[i], getValueByIndex(list, i, &listErrorCode));

            deleteList(list);
            return false;
        }
    }
    deleteList(list);
    return true;
}

const bool test(void)
{
    int testArray1[5] = {1, 5, 7, 4, 2};
    int answerArray1[3] = {1, 7, 2};
    bool testCase1 = testCase(testArray1, 5, answerArray1, 3);

    int testArray2[10] = {5, 4, 8, 23, 6, 45, 1, 65, 11, 4};
    int answerArray2[5] = {5, 8, 6, 1, 11};
    bool testCase2 = testCase(testArray2, 10, answerArray2, 5);

    return testCase2 && testCase2;
}
