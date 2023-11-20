#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#include "AVLTree/AVLTree.h"
#include "String/String.h"
// #include "tests/test.h"

#define PROGRAM_FINISHED_CORRECTLY 0
#define MEMORY_ERROR 1
#define INPUT_ERROR 2
#define TESTS_ARE_NOT_PASSED 3

#define SOMETHING_WENT_WRONG_MESSAGE "Похоже, что то пошло не так\n"

typedef enum UserInput
{
    exitCommand,
    appendCommand,
    getValueCommand,
    checkKeyCommand,
    deleteElementCommand
} UserInput;

const size_t commandsCount = 5;

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
    printf("\nДоступные команды:\n0 – выйти\n1 – добавить в словарь значение по ключу \n2 – получить из словаря значение по ключу\n3 – проверить наличие заданного ключа в словаре\n4 - удалить заданный ключ и значение по нему");
    printf("\nВведите номер, соответствующий команде, которую вы хотите выполнить\n");

    UserInput input = userInput();

    return input;
}

int main(void)
{
    setlocale(LC_ALL, "Rus");
    // if (!test())
    // {
    //     printf("Простите, но программа сейчас не работает\n");
    //     return TESTS_ARE_NOT_PASSED;
    // }

    Dictionary *dictionary = createDictionary();
    if (dictionary == NULL)
    {
        deleteDictionary(dictionary);
        return MEMORY_ERROR;
    }

    DictionaryErrorCode dictionaryErrorCode = ok;
    size_t len = 0;
    UserInput input = checkKeyCommand;
    while (input != exitCommand)
    {
        input = getCommand();
        switch (input)
        {
        case appendCommand:
        {
            printf("Введите ключ: ");
            int key = 0;
            scanfCheck(scanf("%d", &key));
            fgetc(stdin);
            printf("Введите значение: ");
            char *value = getString(&len, stdin, '\n');
            if (value == NULL)
            {
                printf("Недостаточно памяти\n");
                deleteDictionary(dictionary);
                return MEMORY_ERROR;
            }
            dictionaryErrorCode = append(dictionary, key, value, false);
            // free(value);
            break;
        }

        case getValueCommand:
        {
            printf("Введите ключ: ");
            int key = 0;
            scanfCheck(scanf("%d", &key));
            char *value = getValue(dictionary, key);
            if (value == NULL)
            {
                printf("Такого ключа нет в словаре\n");
                break;
            }
            printf("Значение по ключу %d: %s\n", key, value);
            break;
        }

        case checkKeyCommand:
        {
            printf("Введите ключ: ");
            int key = 0;
            scanfCheck(scanf("%d", &key));
            printf("%s", (keyCheck(dictionary, key) ? "Такой ключ есть в словаре\n" : "В словаре нет такого ключа\n"));
            break;
        }

        case deleteElementCommand:
        {
            printf("Введите ключ: ");
            int key = 0;
            scanfCheck(scanf("%d", &key));
            deleteElement(dictionary, key);
            printf("Элемент удален\n");
            break;
        }

        case exitCommand:
        {
            printf("Завершение работы\n");
            deleteDictionary(dictionary);

            exit(PROGRAM_FINISHED_CORRECTLY);
        }

        default:
            break;
        }
    }

    deleteDictionary(dictionary);
    return PROGRAM_FINISHED_CORRECTLY;
}