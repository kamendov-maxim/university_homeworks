#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#include "AVLTree/AVLTree.h"
#include "String/String.h"
#include "tests/test.h"
#include "userInput.h"

#define PROGRAM_FINISHED_CORRECTLY 0
#define MEMORY_ERROR 1
#define INPUT_ERROR 2
#define TESTS_ARE_NOT_PASSED 3

#define SOMETHING_WENT_WRONG_MESSAGE "Похоже, что то пошло не так\n"

const size_t commandsCount = 5;

static void scanfCheck(int scanned, Dictionary *const dictionary)
{
    if (scanned != 1)
    {
        printf("%s", SOMETHING_WENT_WRONG_MESSAGE);
        deleteDictionary(dictionary);
        exit(INPUT_ERROR);
    }
}

static UserInput userInput(Dictionary *const dictionary)
{
    UserInput input = exitCommand;
    scanfCheck(scanf("%d", &input), dictionary);

    while (input >= commandsCount)
    {
        printf("Проверьте правильность ввода\n");
        scanfCheck(scanf("%d", &input), dictionary);
    }

    return input;
}

static const UserInput getCommand(Dictionary *const dictionary)
{
    printf("\nДоступные команды: ");
    printf("\n0 – выйти");
    printf("\n1 – добавить в словарь значение по ключу");
    printf("\n2 – получить из словаря значение по ключу");
    printf("\n3 – проверить наличие заданного ключа в словаре");
    printf("\n4 - удалить заданный ключ и значение по нему");
    printf("\nВведите номер, соответствующий команде, которую вы хотите выполнить\n");

    return userInput(dictionary);
}

static char *getKey(Dictionary *dictionary)
{
    fgetc(stdin);
    printf("Введите ключ: ");
    size_t len = 0;

    char *key = getString(&len, stdin, '\n');
    if (key == NULL)
    {
        printf("Недостаточно памяти\n");
        deleteDictionary(dictionary);
        exit(MEMORY_ERROR);
    }
    return key;
}

int main(void)
{
    setlocale(LC_ALL, "Rus");

    // if (!test())
    // {
    //     printf("К сожалению, сейчас программа не работает\n");
    //     return TESTS_ARE_NOT_PASSED;
    // }

    Dictionary *dictionary = createDictionary();
    if (dictionary == NULL)
    {
        return MEMORY_ERROR;
    }

    DictionaryErrorCode dictionaryErrorCode = ok;
    size_t len = 0;
    UserInput input = checkKeyCommand;
    while (input != exitCommand)
    {
        createRepresentation(dictionary);
        input = getCommand(dictionary);

        switch (input)
        {
        case appendCommand:
        {
            char *key = getKey(dictionary);
            printf("Введите значение: ");
            char *value = getString(&len, stdin, '\n');
            if (value == NULL)
            {
                printf("Недостаточно памяти\n");
                free(key);
                deleteDictionary(dictionary);
                return MEMORY_ERROR;
            }

            dictionaryErrorCode = addElement(dictionary, key, value, false);
            break;
        }

        case getValueCommand:
        {
            char *key = getKey(dictionary);
            char *value = getValue(dictionary, key);
            if (value == NULL)
            {
                printf("Такого ключа нет в словаре\n");
                break;
            }
            printf("Значение по ключу %s: %s\n", key, value);
            free(key);
            break;
        }

        case checkKeyCommand:
        {
            char *key = getKey(dictionary);
            printf("%s", (keyCheck(dictionary, key) ? "Такой ключ есть в словаре\n" : "В словаре нет такого ключа\n"));
            free(key);
            break;
        }

        case deleteElementCommand:
        {
            char *key = getKey(dictionary);
            deleteElement(dictionary, key);
            free(key);
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

    return PROGRAM_FINISHED_CORRECTLY;
}
