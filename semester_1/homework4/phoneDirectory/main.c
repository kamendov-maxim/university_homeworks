#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

#include "phoneBook/phoneBook.h"
#include "String/String.h"
#include "tests/test.h"
#include "userInterface/userInterface.h"

#define PROGRAM_FINISHED_CORRECTLY 0
#define PROGRAM_FAILED_TESTS 1
#define MEMORY_ERROR 2
#define INPUT_ERROR 3
#define READING_FILE_ERROR 4

#define DATABASE_FILENAME "../file.txt"

#define ERROR_MESSAGE "Во время выполнения программы произошла ошибка\n"

int main(void)
{
    setlocale(LC_ALL, "Rus");

    if (!test())
    {
        printf("Программа сейчас не работает\n");
        return PROGRAM_FAILED_TESTS;
    }
    

    PhoneBook *phoneBook = createPhoneBook();
    if (phoneBook == NULL)
    {
        return MEMORY_ERROR;
    }

    if (readFromDataBase(phoneBook, DATABASE_FILENAME) != ok)
    {
        deletePhoneBook(phoneBook);
        return READING_FILE_ERROR;
    }

    Command userInput = exitCommand;
    size_t len = 0;
    do
    {
        userInput = userInterface();
        switch (userInput)
        {
        case addEntryCommand:
        {
            getc(stdin);
            printf("Введите имя: ");
            char *name = getString(&len, stdin, '\n');
            if (name == NULL)
            {
                deletePhoneBook(phoneBook);
                return MEMORY_ERROR;
            }

            printf("Введите номер: ");
            char *number = getString(&len, stdin, '\n');
            if (number == NULL)
            {
                free(name);
                deletePhoneBook(phoneBook);
                return MEMORY_ERROR;
            }

            ErrorCode errorCode = addEntry(phoneBook, name, number, false);
            if (errorCode != ok)
            {
                free(name);
                free(number);
                deletePhoneBook(phoneBook);
                return MEMORY_ERROR;
            }

            break;
        }

        case printEntriesCommand:
        {
            printPhoneBook(phoneBook);
            break;
        }

        case findNumberByNameCommand:
        {
            getc(stdin);
            printf("Введите имя: ");
            char *name = getString(&len, stdin, '\n');
            if (name == NULL)
            {
                deletePhoneBook(phoneBook);
                return MEMORY_ERROR;
            }

            char *foundNumber = findNumberByName(phoneBook, name);
            if (foundNumber == NULL)
            {
                printf("Такого пользователя нет в книге\n");
                break;
            }
            printf("Пользователь %s имеет номер %s\n", name, foundNumber);
            break;
        }

        case findNameByNumberCommand:
        {
            getc(stdin);
            printf("Введите номер: ");
            char *number = getString(&len, stdin, '\n');
            if (number == NULL)
            {
                deletePhoneBook(phoneBook);
                return MEMORY_ERROR;
            }

            char *foundName = findNameByNumber(phoneBook, number);
            if (foundName == NULL)
            {
                printf("Такого номера нет в книге\n");
                break;
            }
            printf("Номер %s принадлежит пользователю %s\n", number, foundName);
            break;
        }

        case saveToFileCommand:
        {
            if (saveToDataBase(phoneBook, DATABASE_FILENAME) != ok)
            {
                deletePhoneBook(phoneBook);
                return READING_FILE_ERROR;
            }

            break;
        }

        case exitCommand:
        {
            printf("Завершение работы\n");
            continue;
        }

        default:
            break;
        }
    } while (userInput != exitCommand);
    return PROGRAM_FINISHED_CORRECTLY;
}
