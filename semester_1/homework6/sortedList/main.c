#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

#include "list/list.h"
#include "tests/test.h"

#define PROGRAM_FINISHED_CORRECTLY 0
#define MEMORY_ERROR 2
#define PROBLEM_WITH_LIST 3
#define INPUT_ERROR 4
#define TESTS_ARE_NOT_PASSED 5

#define SOMETHING_WENT_WRONG_MESSAGE "Похоже, что то пошло не так\n"

typedef enum UserInput
{
    exitCommand,
    appendCommand,
    popCommand,
    printCommand
} UserInput;

const size_t commandsCount = 4;


static void scanfCheck(int scanned)
{
    if (scanned != 1)
    {
        printf("%s", SOMETHING_WENT_WRONG_MESSAGE);
        exit(INPUT_ERROR);
    }
}

static UserInput userInput(void)
{
    UserInput input = exitCommand;
    scanfCheck(scanf("%d", &input));

    while (input >= commandsCount)
    {
        printf("Проверьте правильность ввода\n");
        scanfCheck(scanf("%d", &input));
    }

    return input;
}

static const UserInput getCommand(void)
{
    printf("\nДоступные команды:\n0 – выйти\n1 – добавить значение в сортированный список\n2 – удалить значение из списка\n3 – распечатать список\n");
    printf("\nВведите номер, соответствующий команде, которую вы хотите выполнить\n");

    UserInput input = userInput();

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

    List *list = createList();
    if (list == NULL)
    {
        printf("Недостаточно памяти\n");

        return MEMORY_ERROR;
    }

    ListErrorCode listErrorCode = ok;
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
            int value = 0;
            scanfCheck(scanf("%d", &value));

            listErrorCode = append(list, value);
            if (listErrorCode != ok)
            {
                printf("%s", SOMETHING_WENT_WRONG_MESSAGE);
                return PROBLEM_WITH_LIST;
            }
            break;
        }

        case printCommand:
            printList(list);
            break;

        case popCommand:
        {
            printf("Введите значение, которое вы хотите удалить:\n");
            int value = 0;
            scanfCheck(scanf("%d", &value));
            listErrorCode = pop(list, value);
            if (listErrorCode != ok)
            {
                printf("Проверьте правильность ввода\n");
                break;
            }
            break;
        }

        case exitCommand:
            deleteList(list);
            return PROGRAM_FINISHED_CORRECTLY;
            break;
        }
    }

    return PROGRAM_FINISHED_CORRECTLY;
}
