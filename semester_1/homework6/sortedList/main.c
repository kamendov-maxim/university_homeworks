#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

#include "list/list.h"
#include "tests/test.h"
#include "getString/getString.h"

#define PROGRAM_FINISHED_CORRECTLY 0
#define MEMORY_ERROR 2
#define PROBLEM_WITH_LIST 3
#define INPUT_ERROR 4
#define TESTS_ARE_NOT_PASSED 5

typedef enum UserInput
{
    exitCommand,
    appendCommand,
    popCommand,
    printCommand,
    error
} UserInput;

static const UserInput getCommand(void)
{
    printf("\nДоступные команды:\n0 – выйти\n1 – добавить значение в сортированный список\n2 – удалить значение из списка\n3 – распечатать список\n");
    printf("\nВведите номер, соответствующий команде, которую вы хотите выполнить\n");

    UserInput input = exitCommand;
    size_t scanned = scanf("%d", &input);
    if (scanned != 1)
    {
        return error;
    }

    while (input != exitCommand && input != appendCommand && input != popCommand && input != printCommand)
    {
        printf("Проверьте правильность ввода\n");
        size_t scanned = scanf("%d", &input);
        if (scanned != 1)
        {
            return error;
        }
    }

    return input;
}

int main()
{
    setlocale(LC_ALL, "Rus");

    if (!test())
    {
        printf("Простите, но программа сейчас не работает\n");
        return TESTS_ARE_NOT_PASSED;
    }

    setlocale(LC_ALL, "Rus");

    ListErrorCode listErrorCode = ok;
    List *list = createList(&listErrorCode);
    if (listErrorCode != ok)
    {
        printf("Похоже, что то пошло не так\n");

        return PROBLEM_WITH_LIST;
    }

    UserInput input = printCommand;
    while (input != exitCommand)
    {
        UserInput input = getCommand();
        
        switch (input)
        {
        case appendCommand:
        {
            size_t len = 0;
            printf("Ведите значение, которое вы хотите добавить\n");
            // char *value = getString(&len);
            // printf("%d\n", len);
            // printf("dasaf");
            int value = 0;
            if (scanf("%d", &value) != 1)
            {
                printf("Похоже, что то пошло не так\n");
                return INPUT_ERROR;
            }

            listErrorCode = append(list, value);
            if (listErrorCode != ok)
            {
                printf("Похоже, что то пошло не так\n");
                return PROBLEM_WITH_LIST;
            }
            break;
        }

        case printCommand:
            printList(list);
            break;

        case popCommand:
        {
            printf("Введите индекс элемента, который вы хотите удалить:\n");
            size_t index = 0;
            if (scanf("%zu", &index) != 1)
            {
                printf("Похоже, что то пошло не так\n");
                return INPUT_ERROR;
            }
            listErrorCode = popByIndex(list, index);
            if (listErrorCode != ok)
            {
                printf("Проверьте правильность ввода\n");
                break;
            }
            break;
        }

        case error:
            break;

        case exitCommand:
            deleteList(list);
            return PROGRAM_FINISHED_CORRECTLY;
            break;
        }
    }

    deleteList(list);

    return PROGRAM_FINISHED_CORRECTLY;
}
